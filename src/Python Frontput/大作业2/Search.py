import os
import xml.etree.ElementTree as ET
import tkinter as tk
from tkinter import ttk
from tkinter import Scrollbar, filedialog
import re
import threading

stop_search = False

def extract_pages(file_path):
    if not os.path.exists(file_path):
        tk.messagebox.showerror("错误", f"文件 {file_path} 不存在")
        return
        
    with open(file_path, "r", encoding="utf-8") as f:
        inside_page = False
        page_content = []
        try:
            for line in f:
                if "<page>" in line:
                    inside_page = True
                    page_content = [line]
                elif "</page>" in line:
                    page_content.append(line)
                    yield "".join(page_content)
                    inside_page = False
                    page_content = []
                elif inside_page:
                    page_content.append(line)
        except Exception as e:
            print(e)

def search_term_in_pages(term, file_path):
    global stop_search
    for page_content in extract_pages(file_path):
        if stop_search:
            break
        try:
            root = ET.fromstring(page_content)
            page_id = root.find("id").text
            title_elem = root.find("title")
            title = title_elem.text if title_elem is not None else "无标题"
            contributor_elem = root.find("revision/contributor/username")
            contributor = contributor_elem.text if contributor_elem is not None else "未知"
            text_elem = root.find("revision/text")
            text_content = text_elem.text if text_elem is not None else ""
            if (text_content and re.search(re.escape(term), text_content, re.IGNORECASE)) or (title and re.search(re.escape(term), title, re.IGNORECASE)):
                highlighted_text = re.sub(
                    f"({re.escape(term)})", r"*\1*", text_content, flags=re.IGNORECASE
                )
                yield {"id": page_id, "title": title, "contributor": contributor, "text": highlighted_text}
        except ET.ParseError:
            continue

def perform_search(search_term, file_path):
    for row in results_tree.get_children():
        results_tree.delete(row)
    for result in search_term_in_pages(search_term, file_path):
        if re.search(re.escape(search_term), result["title"], re.IGNORECASE):
            results_tree.insert(
                "",
                0,
                values=(result["id"], result["title"], result["contributor"], result["text"][:100] + "...")
            )
        else:
            results_tree.insert(
                "",
                "end",
                values=(result["id"], result["title"], result["contributor"], result["text"][:100] + "...")
            )
        root.update_idletasks()

def on_search():
    global stop_search
    stop_search = False
    search_term = search_entry.get()
    file_path = file_path_entry.get()
    search_thread = threading.Thread(target=perform_search, args=(search_term, file_path))
    search_thread.start()

def stop_searching():
    global stop_search
    stop_search = True

def browse_file():
    file_path = filedialog.askopenfilename(filetypes=[("XML files", "*.xml")])
    if file_path:
        file_path_entry.delete(0, tk.END)
        file_path_entry.insert(0, file_path)

root = tk.Tk()
root.title("Wiki搜索")

default_directory = os.getcwd()
default_file_path = os.path.join(default_directory, "zhwiki.xml")

xml_frame = tk.Frame(root)
xml_frame.pack(pady=5)

file_path_label = tk.Label(xml_frame, text="XML文件位置：")
file_path_label.pack(side=tk.LEFT,pady=5)
file_path_entry = tk.Entry(xml_frame, width=50)
file_path_entry.insert(0, default_file_path)
file_path_entry.pack(side=tk.LEFT,pady=5)

browse_button = tk.Button(xml_frame, text="浏览", command=browse_file)
browse_button.pack(side=tk.LEFT,pady=5)

search_label = tk.Label(root, text="输入搜索词：")
search_label.pack(pady=5)
search_entry = tk.Entry(root, width=50)
search_entry.pack(pady=5)

button_frame = tk.Frame(root)
button_frame.pack(pady=5)

search_button = tk.Button(button_frame, text="搜索", command=on_search)
search_button.pack(side=tk.LEFT, padx=5)

stop_button = tk.Button(button_frame, text="停止", command=stop_searching)
stop_button.pack(side=tk.LEFT, padx=5)

scrollbar = Scrollbar(root)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

results_tree = ttk.Treeview(root, columns=("ID", "标题", "贡献者", "文本"), show="headings", yscrollcommand=scrollbar.set)
results_tree.heading("ID", text="页面ID")
results_tree.heading("标题", text="标题")
results_tree.heading("贡献者", text="贡献者")
results_tree.heading("文本", text="文本")
results_tree.column("ID", width=100)
results_tree.column("标题", width=200)
results_tree.column("贡献者", width=150)
results_tree.column("文本", width=600)
results_tree.pack(pady=10, fill=tk.BOTH, expand=True)

scrollbar.config(command=results_tree.yview)

root.mainloop()
