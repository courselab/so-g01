<!--
   SPDX-FileCopyrightText: 2021 Monaco F. J. <monaco@usp.br>
  
   SPDX-License-Identifier: GPL-3.0-or-later

   This file is part of SYSeg, available at https://gitlab.com/monaco/syseg.
-->

 SYSeg Manual
==============================

TL;DR

- As part of an undergraduate scientific program at the university, the author
  did some research work at the institute of physics. There was this huge and
  intimidating high-tech precision measurement equipment that mainly resembled
  an alien artifact straight out of a sci-fi movie. On a stainless-steel tag
  attached to the device, a short, subtly ironic note, read:

  _After all solo assembling attempts have failed, read the instruction manual._

 Introduction
 ------------------------------

 SYSeg (System Software, e.g.) is a collection of source-code examples and 
 programming exercises intended to illustrate general concepts and techniques 
 related to system software design and implementation. 

 The package has been compiled from class notes in undergraduate courses in
 Computer Science and Engineering, and is meant to  be useful for students
 and instructors exploring low-level programming.

 SYSeg is distributed under the license GNU GPL vr.3 or later version.

 See file `AUTHORS` for contributors and contact information.

 Essential Information
 ------------------------------

 Each subdirectory in the source tree has a file `README` which contains
 important instructions on how use the directory's contents. 

 Please, as the the name suggests, do read the information --- that shall 
 assuredly save you precious time. 

 If you find a file named `README.m4`, this is not the file you're looking
 for; it's a source file that is used by SYSeg be create the actual `README`.
 If you find the source `README.m4` file but not the corresponding `README`
 file in the same directory, changes are that you have missed the package
 configuration procedure described bellow. If so, please go through the
 step-by-step directions and proceed as explained below.

 Requirements
 ------------------------------
 
 SYSeg was designed to be executed on the GNU/Linux operating systems, for
 the x86 hardware platform (aka the standard PC computer).

 WINDOWS AND MAC USERS
 
 There have been reports of users being able to try SYSeg on Linux running in 
 a virtual machine over Microsoft Windows, as as well on WSL (Windows Subsystem
 for Linux). Such configurations have not been fully tested, though. 

 The examples should work on MacOS, although such possibility has not being
 fully and systematically tested either.

 If you decide to try a setup like those, feedback will be much appreciated.

 DEPENDENCIES

 In order to build and execute SYSeg code examples, the following pieces of
 software may be needed. Some are strictly required and should be installed
 in your system; others may be used only by some examples and their
 installation is optional, depending on the functionality you want to try.

 The SYSeg configuration scripts should guide you during the build procedure,
 and the instructions relative to each code example should also give further
 instructions.

 If a particular package is requested, the list bellow indicates the lowest
 version against which SYSeg examples have been tested. Using a more recent
 version should be fine, but it is not absolutely guaranteed that results
 won't exhibit (hopefully) minor variations. Feedback is always appreciated
 (feel free to open an issue at the official repository).

 It should be safe to use

 - Linux         5.13.0         (any decent ditribution)
 - Bash		 4.4-18		(most shell scripts need bash)
 - GCC 	     	 9.3.0	        (the GNU compiler)
 - GNU binutils  2.34		(GNU assembler, linker, disassembler etc.)
 - GNU coreutils 8.30		(basic utilities, probably already installed)
 - nasm		 2.14.02	(NASM assembler)
 - qemu		 4.2.1		(x86 emulator, specifically qemu-system-i386)
 - gcc-multilib  9.3.0		(to compile 16/32-bit code in a 64-bit platform)
 - xorriso	 1.5.2-1	(depending on your computer's BIOS)
 - hexdump	 POSIX.2	(binary editor)
 - meld		 3.20		(graphical diff tool, optional)
 - Git		 2.34.1		(some SYSeg scripts use git under the hood).
 - pipx		 1.0.0		(this dependence will eventually be deprecated)
 - reuse-tool    (see below)	(for REUSE/SPDX standard compliance)

 SYSeg uses the FSFE's REUSE helper tool. Currently, though, some of the desired
 features of reuse-tool are available only via a few patches. For convenience,
 this SYSeg release uses a custom version of the tool which can be installed
 from the SYSeg author's repository. The setup instructions described bellow
 should assist you in this procedure.

 Setup Instructions (IMPORTANT)
 ------------------------------
 
 Some examples in SYSeg need auxiliary artifacts which must be built beforehand.

 If you have obtained SYSeg source from the its official VCS repository (i.e.
 you have cloned it from the mainstream Git repository), then execute the 
 following script, found at the top of the project's source tree:

 ```
  $ ./bootsrap.sh
 ```

 This will create the build configuration script `configure`.

 Perhaps you are already familiar with the GNU build system but, if you are not,
 no worries. The `configure` script is meant to check if your system meet all
 the requirements for building SYSeg, as a result, `configure` will create
 a customized build procedure that takes into account your compiler version,
 system libraries etc.

 The script `bootstrap.sh` requires that you have the GNU build system, 
 aka Autotools, installed in your computer. In an apt-based Linux distribution,
 for instance, you may install Autotools with

```
 $ sudo apt install automake autoconf libtool
```

 On the other hand, if you have obtained the software in the form a
 __pre-initialized distribution bundle__, usually as a tarball, you should
 already have the  script `configure` pre-built and thus you will not need
 Autotools (you may then safely skip the Autotools installation step above).

 Either way, locate the file in the root of SYSeg source directory tree
 and execute it

```
 $ ./configure
```

 This script shall perform a series of tests to collect data about the build 
 platform. If it complains about missing pieces of software, install them 
 as needed and rerun `configure`. The file `syseg.log` contains a summary
 of the last execution of the configuration script.

 Finally, build the software with

```
 $ make
```

 **Note** that, as mentioned, this procedure is intended to build the auxiliary
 tools needed by SYSeg. The examples and programming exercises themselves will
 not be built as result of the main configuration script being executed. The
 process of building the example code in each subdirectory is part of the skills
 that each example and programming exercise is meant to exercise.

 To build each example or programming exercise, one needs to access the
 subdirectory containing the respective source code and follow the instructions
 indicated in the corresponding `README` file (found in that respective
 subdirectory.)

 The file `INSTALL` (that should exist after you have bootstrapped the project)
 contains detailed instruction on how to customize SYSeg build and installation.

 If you intend to try the proposed programming exercises according to the given 
 directions, you will need to install SYSeg tools locally. To that end, execute

```
 $make install
```

 This should install SYSeg auxiliary scripts, programs and data files under
 `$HOME/.syseg`. You won't need to add that location to the `PATH` environment
 variable, as the tools that need to access the resources in it will know
 where to find them. Do not build or install SYSeg as the `root` user, nor use
 `sudo` to perform those tasks.

 SYSeg Contents
 -------------------------------

 The file `README.md`, at the top of SYSeg source tree, contains a summary of
 the project directory structured. In each individual sub-directory, there
 should be a file `README` further detailing its contents. Remember, you need
 to build SYSeg in order to generate the `README` files.

 Reusing SYSeg Code
 ------------------------------
 
 SYSeg is open source; you may freely reuse portions of it in your work.

 However, please take notice of the following directions.

 COPYRIGHT AND LICENSING LITERACY

 If you reuse third-party's source code in your own project, and modify that
 code, then, under the international copyright convention, you have created
 a 'derivative work'. The derivative work is now a production of multiple
 authors: the author(s) of the original code you copied, and you, who made
 changes to that work. Being your project a derivative work, you share its
 copyright with the copyright holder of the original work that you modified.

 The proper way to handle this shared authorship is to keep any copyright
 and licensing notice present in the material, and add your name as an
 additional copyright holder. Also, bear in mind that you may only redistribute
 your derivative work in accordance with the license of the original work ---
 you may chose a different license, but this license must not conflict with the
 terms of the license under which the original work' is distributed (beware
 that the derivative work can then be redistributed under both licenses).
 
 To assist you in addressing these requirements, SYSeg offers a script that
 you can use to export files from SYSeg to your project. You can invoke the
 script like this

     `tools/syseg-export <original-file> <destination-directory>`

 The script will copy the original file into the destination directory
 and change the copyright notice (the comments at the top of the file)
 with the correct information. The script will also annotate the file
 with proper attribution for the original author.

 You can subsequently edit the information if you wish, for instance, to
 add the names of other authors (or they can add themselves through the
 same procedure, as described).

 Proposed Exercises
 ------------------------------
 
 In addition to code examples, SYSeg contains also some proposed implementation
 challenges which can be found in directory `syseg/try`.

 Users interested in practicing skills on system software design and
 implementation are encouraged to explore the programming exercises.

 Instructors are welcome, as well, to use SYSeg's exercises to teach their
 students. SYSeg provides some handy tools for this purpose, including
 scripts to prepare bootstrap code and directions to deliver the activities
 through a VCS repository.

 If you reuse SYSeg code either in your classes or implementation project,
 you are kindly invited to drop the author a message. It's always nice to
 know who else is exploring the material.

 USING BOOTSTRAP CODE

 If the specification of a SYSeg programming exercise provides some bootstrap
 code for you to build upon, please, do not simply copy the individual files
 to your project. 

 Some examples and bootstrap code work in conjunction with other components of
 SYSeg and may require either that you modify the source or copy complementary
 files into your project --- if you don't, you may end up with incomplete or
 non-functional code.

 Moreover, as explained before, if you just copy the files, this may result
 in your project having legally misleading copyright and licensing information.

 Instead, proceed as indicated in the 'README' file in respective directory.

 Unless otherwise indicated, the basic workflow to start working with the
 SYSeg programming exercise requires you to use the script

    `tools/syseg-project <some-path>/<project-name>`

 to create a new project for you to solve the programming exercise. The script
 should create a directory named after your project name, and populate it with
 scripts, data files, documentation files and other resources required for the
 bootstrap code to work from a stand-alone directory outside the SYSeg source
 directory tree.

 Then, if a given implementation exercise provides some bootstrap code for you
 to build upon, its specification will instruct you to export the code from
 SYSeg into your newly created project using the aforementioned export facility.
 Usually, the directory containing the exercise should provide you with a
 Makefile implementing a rule specifically to assist you in this procedure:


   `make export` 

 The Makefile rule should create a tarball within the current
 directory, containing all the files relevant for that exercise. You
 should then copy/move the the tarball into your project directory and
 uncompress it there. Enter de newly created subdirectory of your
 project and develop the immplementation challenge.

 When you are finished with the exercise, deliver your working using the method
 described in the aforementioned README file. As a suggestion, SYSeg's exercises
 will probably instruct you to commit your changes into a VCS (e.g. Git)
 repository and tag it with a delivery identifier (if not specified in the
 exercise documentation, use 'done' for the first delivery. If you
 need to submit a revised version, use the 'rev1',  'rev2' and so on).

 To tag your project:

 ```
   git tag done
   git push origin done
 ```
 
 Conventions
 ------------------------------

 The file `doc/conventions.md` summarize some conventions used throughout
 the documentation and source code examples.

 Contributing
 ------------------------------
 
 Bug reports and suggestions are always welcome: feel free to open and issue
 at the version-control repository, or to contact the author directly.

 The file 'AUTHORS' lists all contributors and acknowledgments, with
 respective contact information.

 Should you like to contribute, please, refer to the file `CONTRIBUTING.md`.

 Licensing
 -----------------------------
 
 SYSeg (system-software, _exempli gratia_)
 Copyright (c) 2021 Monaco F. J. <monaco@usp.br>. 

 SYSeg is free software and can be distributed under the terms of GNU General
 Public License version 3 of the license or, at your discretion, any later 
 version. Third-party source files distributed along with SYSeg are made 
 covered by their respective licenses, as annotated in each individual file.

 See the terms of each license under the directory LICENSES. 

 Troubleshooting
 ------------------------------   
   
 If you ever find any trouble using SYSeg, consider the following tips.

### I can see a `README.m4` or a `Makefile.m4` file in a given directory,
    but can't find the corresponding `README` or `Makefile` file.

    This probably happens because you've missed the installation instructions.
   
   To fix the issue:
   
   ```
   cd <path>/syseg
   ./bootstrap.sh
   ./configure
   make
   ```
   
### I edited a Makefile.m4 and need to update the corresponding Makefile
 
   Within the directory containing the edited `Makefile.am`, invoke:
   
   ```
   make -C ..
   ```
   
### I tried everything to no avail.

    You're welcome to drop a message to the author.