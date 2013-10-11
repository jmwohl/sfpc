# Using Sublime for C++ and openFrameworks.md

First, a brief preface:  **I am new to C/C++, new to gcc/g++, new to make and Makefiles, and new to openFrameworks.**  I am not entirely new to software development though, and I guess I have strong opinions about the tools that I use.  And maybe I'm resistant to change.  More than anything, I like to know how things work, and don't like being confused.  So when I started with C/C++ with Xcode, it was frustrating — the tool was foreign, felt heavy and slow, and didn't let me work the way I was used to.

### Setting up SublimeText for C/C++ development

**NOTE: This guide is for SublimeText 2, not 3.  Unfortunately there doesn't seem to be a good code completion package for SublimeText 3 yet.**

Two things I knew were going to be important to me: smart code hinting and completion, and auto formatting.  Thankfully other folks had already solved these problems for me via a couple handy packages:

    1) SublimeAStyleFormatter - for auto formatting, with lots of configurable options
    2) SublimeClang - for code completion, also configurable

I installed both via the Package Control.

#### Setting up SublimeClang Package

In order to get code completion working, I had to add include paths for my version of Xcode and openFrameworks.  After installing SublimeClang, go to *Preferences->Package Settings->SublimeClang->Settings User* and make it looks like this, changing the paths to the correct paths for your computer:

```
{
    "options": [ 
        "-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk/usr/include",
        "-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk/usr/include/c++/4.2.1",
        "-I/usr/local/lib/OF/0.8.0/libs/**",
        "-I/usr/local/lib/OF/0.8.0/addons/**"
    ]
}
```

The bottom two are symlinks that I created in /usr/local/lib, which seems be to where libs naturally go.   They link to the libs and addons directories that I keep elsewhere on my computer.  That "-I" at the beginning is the clang flag for 'include path'.

### The Good Stuff - openFrameworks Development

Now here's the exciting part:  It's entirely EASY to build OF projects without Xcode!  Who knew?  Turns out that projects created with the Project Generator include a Makefile that is already set up to work with make.  In order to get things working nicely with SublimeText, I created a new build system called OF.  To create a new build system go to *Tools->Build System->New Build System...*, and add the following:

```
{
    "cmd": ["cd '$project_path' && make Debug && make run Debug"],
    "shell": true,

    "variants": [
        { 
            "cmd": ["cd '$project_path' && make && make run"],
            "name": "OF Release and Run",
            "shell": true
        },
        { 
            "cmd": ["cd '$project_path' && make clean"],
            "name": "OF Clean",
            "shell": true
        }
    ]
}
```

With this in place you can hit cmd-b while working in the project and sublime will build the Debug version of the application, then run it!  Wooo hooo!  The other varients make it possible to run the 'Release' build or clean (remove built apps) using the package commands.  (Hit shift-cmd-P, start typing the name of the command.)

One minor caveat: the project does need to be an actual SublimeText project in order for the builds to work, since they use the $project_path variable.

*NOTE:* The app that gets built is a directory with the .app extension, so clean didn't actually remove it properly.  In order to get the clean running, I did have to modify the compile.project.mk make file supplied by openFrameworks.  I added the following after line 310:

```
# in openFrameworks_0.8.0/libs/openFrameworksCompiled/project/makefileCommon, after line 310
rm -rf $(TARGET).app
```

### Additional Notes

You should be able to build now by hitting **cmd-b**.  If the application that gets built ends up with a weird name, it might be because the path to the src has spaces in it - this was the case for me.  You can explicitly set a name in config.make using 

```
APPNAME = SomeName
```

### Overview of the Process So Far

Ok.  Now we should be able to work on new OF projects by following these steps:

    1) Create a new OF project with the projectGenerator
    2) In the terminal, navigate to the generated project dir, and type ```subl .``` to open it in sublime.
    3) Once the project opens, choose *Project->Save Project As...* from the menu and give it the same name as you did in the project generator.
    4) Start writing code!  When you're ready to build, hit **cmd-b**.