## Description 
###### Made for mac
The Latex Autobuilder is...an autobuilder for LaTeX.

It takes in the name of a `.tex` file, and waits for the file to change. Upon changing, the code will then remake the pdf and show it to screen.

## Requirements
- [BasicTex](http://www.tug.org/mactex/morepackages.html)
- [Clang](https://releases.llvm.org/download.html)

## Usage
1. Navigate to the folder containing `latex_autobuilder.c`
  ```console
  cd /path/to/latex_autobuilder
  ```
2. Create the executable 
  ```console
  clang latex_autobuilder.c -o latexab
  ```
3. Run the executable with the name of your `.tex` file as input
  ```console
  ./latexab "Filename"
  ```
4. When finished, either close the termnial or `control +  C`
