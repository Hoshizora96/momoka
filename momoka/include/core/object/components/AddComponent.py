# coding: utf-8
# 这个脚本是用来自动生成GameEntityPool.h文件的
import os
from datetime import datetime

target = "../GameObjectPool.h"

include_prefix_index = os.path.abspath(os.curdir).find("include") + len("include") + 1
include_path = os.path.abspath(os.curdir)[include_prefix_index:].replace("\\", "/") + "/"

include_file_names = []
components_list = []

for path, directories, filenames in os.walk(os.curdir):
    for filename in filenames:
        if(filename.find(".py")>0 or filename.find("Component.h")<=0):
            continue
        include_file_names.append(include_path + filename)
        if(filename != filenames[-1]):
            components_list.append(filename.replace(".h", ""))

now = datetime.now()
s = now.strftime('%Y/%m/%d %H:%M:%S')

template = "#pragma once\n\n"
template += "// 已安装{0}个组件\n".format(str(len(components_list)))
template += "// 更新时间：{0}\n\n".format(s)
template += "#include \"core/object/EntityPool.h\"\n"

for i in include_file_names:
    template += "#include \"{0}\"\n".format(i)

template += "\n"
template += "using GameEntityPool = EntityPool<\n"
template += "\t// 以下参数列表为安装的组件\n"


for i in components_list:
    template += "\t" + i
    if(i != components_list[-1]):
        template += ","
    template += "\n"


template += ">;"

print(template)

f = open(target, "w")
f.write(template)
f.close()
    