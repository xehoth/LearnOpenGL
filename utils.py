# -*- coding: utf-8 -*-
import os
import platform
import sys
import shutil

buildDir = "build/src/"
binDir = "bin/"
targets = {"HelloWorld", "CreateWindow"}
targetDeps = {}
system = platform.system()


def clean():
    if os.path.exists("build"):
        shutil.rmtree("build")
    if os.path.exists("bin"):
        shutil.rmtree("bin")


def build():
    clean()
    os.mkdir("build")
    buildFlag = True

    if system == "Windows":
        buildFlag = os.system(
            'cd build && cmake -G "Visual Studio 16 2019" .. && cmake --build . --config Release')
    else:
        buildFlag = os.system(
            'cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build . -j4')

    if buildFlag:
        print("build failed")
        return False

    os.mkdir("bin")

    def getTargetPath(s):
        if system == "Windows":
            return buildDir + s + "/Release/" + s + ".exe"
        return buildDir + s + "/" + s

    for i in targets:
        shutil.move(getTargetPath(i), binDir)

    shutil.rmtree("build")
    shutil.copytree("res", binDir + "res")

    print("build done")
    return True


def printHelp():
    print("usage: [build] [run <target>] [clean] [--help]")


def runTarget(target):
    if system == "Windows":
        os.system("cd " + binDir + " && " + target)
    else:
        os.system("cd " + binDir + " && ./" + target)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        printHelp()
        sys.exit(0)
    cmd = sys.argv[1]
    if cmd == "--help" or cmd == "-h":
        printHelp()
    elif cmd == "build":
        build()
    elif cmd == "run":
        if len(sys.argv) < 3:
            print("please input a target to run, available targets are:")
            print(targets)
            sys.exit(0)
        runTarget(sys.argv[2])
    elif cmd == "clean":
        clean()
    else:
        print("unknown option " + cmd)
        printHelp()
