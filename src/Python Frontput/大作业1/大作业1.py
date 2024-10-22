import tkinter as tk
from tkinter import filedialog, messagebox
from tkinter.scrolledtext import ScrolledText
import os,re

def load_pinyin_map(filename):
    pinyin_map = {}
    is_text_section = False
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()
            if line == "[Text]":
                is_text_section = True
                continue
            elif not is_text_section or not line:
                continue

            word = ''
            pinyin = ''

            for c in line:
                if c == ' ':
                    continue
                elif c in 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ':
                    pinyin += c
                else:
                    word += c
            
            pinyin_map[word] = pinyin

    return pinyin_map

def annotate_pinyin(sentences, pinyin_map):
    pyr = re.compile(r'(b|p|m|f|d|t|n|l|g|k|h|j|q|x|zh|ch|sh|r|z|c|s|y|w)?(iang|iong|uang|uang|ang|eng|ing|ong|ian|iao|uai|uan|ai|ei|ao|ou|ia|ie|ue|ua|ui|uo|ve|er|an|en|in|un|a|o|e|i|u)')
    ans = []
    for sentence in sentences:
        sentence = sentence.strip()
        cur_ans = ''
        l = len(sentence)
        i = 0
        while i < l:
            j = l
            while j > i:
                word_to_match = sentence[i:j]
                if word_to_match in pinyin_map:
                    pinyin = pinyin_map[word_to_match]
                    py_list = pyr.findall(pinyin)
                    for cur_id in range(len(word_to_match)):
                            cur_ans += word_to_match[cur_id] + '（' + py_list[cur_id][0] + py_list[cur_id][1] + '）'
                    i = j
                    break
                j -= 1
            while i < l and not sentence[i] in pinyin_map:
                cur_ans += sentence[i]
                i+=1
        
        ans.append(cur_ans)
            
    return ans

def select_input_file():
    filename = filedialog.askopenfilename(title="选择输入文件", filetypes=[("文本文件", "*.txt")])
    if filename:
        input_path.set(filename)
        with open(filename, 'r', encoding='utf-8') as file:
            input_text.delete(1.0, tk.END)
            input_text.insert(tk.END, file.read())

def select_output_file():
    filename = filedialog.asksaveasfilename(title="选择输出文件", defaultextension=".txt", filetypes=[("文本文件", "*.txt")])
    if filename:
        output_path.set(filename)

def convert():
    try:
        pinyin_map = load_pinyin_map(os.path.join(os.getcwd(), "winpy.txt"))

        with open(input_path.get(), 'r', encoding='utf-8') as fin, open(output_path.get(), 'w', encoding='utf-8') as fout:
            sentences = fin.readlines()
            annotated_sentences = annotate_pinyin(sentences, pinyin_map)
            for sentence in annotated_sentences:
                fout.write(sentence + '\n')
            output_text.delete(1.0, tk.END)
            output_text.insert(tk.END, '\n'.join(annotated_sentences))
            
        messagebox.showinfo("完成", "拼音标注完成，文件已保存。")
    except Exception as e:
        messagebox.showerror("错误", f"转换失败：{e}")

root = tk.Tk()
root.title("汉字拼音标注工具")
root.geometry("750x550")

frame_center = tk.Frame(root)
frame_center.pack(pady=5)
tk.Label(frame_center, text="winpy.txt路径:").pack(side=tk.LEFT)
winpy_file = tk.Entry(frame_center, width=40)
winpy_file.pack(side=tk.LEFT, padx=5)
winpy_file.insert(0, os.path.join(os.getcwd(), "winpy.txt"))

frame_files = tk.Frame(root)
frame_files.pack(fill=tk.X, expand=True, padx=10, pady=5)

frame_left = tk.Frame(frame_files)
frame_left.pack(side=tk.LEFT, fill=tk.Y)
frame_right = tk.Frame(frame_files)
frame_right.pack(side=tk.RIGHT, fill=tk.Y)

tk.Label(frame_left, text="输入文件:").pack()
input_path = tk.StringVar()
tk.Entry(frame_left, textvariable=input_path, width=30).pack()
tk.Button(frame_left, text="选择输入文件", command=select_input_file).pack(pady=5)
tk.Label(frame_left, text="输入文件内容:").pack()
input_text = ScrolledText(frame_left, wrap=tk.WORD, width=40, height=15)
input_text.pack()

tk.Label(frame_right, text="输出文件:").pack()
output_path = tk.StringVar()
tk.Entry(frame_right, textvariable=output_path, width=30).pack()
tk.Button(frame_right, text="选择输出文件", command=select_output_file).pack(pady=5)
tk.Label(frame_right, text="输出文件内容:").pack()
output_text = ScrolledText(frame_right, wrap=tk.WORD, width=40, height=15)
output_text.pack()

tk.Button(root, text="转换", command=convert, width=15).pack(pady=10)

root.mainloop()
