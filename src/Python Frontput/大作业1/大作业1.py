import tkinter as tk
from tkinter import filedialog, messagebox
from tkinter.scrolledtext import ScrolledText
import os

def load_pinyin_map(filename):
    pinyin_map = {}
    is_text_section = False
    with open(filename, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()
            if line == "[Text]":
                is_text_section = True
                continue
            elif line.startswith("[") and line.endswith("]"):
                is_text_section = False
            if is_text_section:
                if not line or '=' in line:
                    continue
                char = line[:-2]
                pinyin = line[-2:]
                if char in pinyin_map:
                    if len(char) > len(pinyin_map[char]):
                        pinyin_map[char] = pinyin
                else:
                    pinyin_map[char] = pinyin
    return pinyin_map

def annotate_pinyin(input_file, output_file, pinyin_map):
    with open(input_file, 'r', encoding='utf-8') as infile, open(output_file, 'w', encoding='utf-8') as outfile:
        for line in infile:
            annotated_line = ""
            i = 0
            while i < len(line):
                matched = False
                for j in range(len(line), i, -1):
                    sub_str = line[i:j]
                    if sub_str in pinyin_map:
                        annotated_line += f"{sub_str}（{pinyin_map[sub_str]}）"
                        i = j
                        matched = True
                        break
                if not matched:
                    annotated_line += line[i]
                    i += 1
            outfile.write(annotated_line)

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
        annotate_pinyin(input_path.get(), output_path.get(), pinyin_map)
        with open(output_path.get(), 'r', encoding='utf-8') as file:
            output_text.delete(1.0, tk.END)
            output_text.insert(tk.END, file.read())
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
