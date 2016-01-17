import os
import string

NO_EXPLORE = [".git", "include", ".idea"]
ROOT = "./"

def explore():
    list_of_subdirectories = [x[0] for x in os.walk(ROOT)]
    src = ""
    for elt in list_of_subdirectories:
        c = True
        for d in NO_EXPLORE:
            if d in elt:
                c = False
        if c:
            if os.path.isfile(elt + "/makesrc"):
                makesrc = open(elt  + "/makesrc", "r")
                file_list = makesrc.readlines()
                for f in file_list:
                    if f != "":
                        if f[0] != "#":
                            src += (elt[len(ROOT)::] + "/" + f + " ")
                makesrc.close()

    if len(src) > 0:
        src = src.replace('\r', '');
        src = src.replace('\n', '');

        src = src.replace("\\", "/")

        print(src)

explore()
