# ULS

## Synopsys

    ./uls [-ACFGRSTU@acfghilmoprtux1] [file ...]

## Description

Implementation of the famous Unix command ```ls```, using the C programming 
language.

For each operand that names a file of a type other than directory, ```uls```
displays its name as well as any requested, associated information.  For each
operand that names a file of typedirectory, ```uls``` displays the names of
files contained within that directory, as well as any requested, associated
information.

If no operands are given, the contents of the current directory are displayed.
If more than one operand is given, non-directory operands are displayed first;
directory and non-directory operands are sorted separately and in
lexicographical order.

## How to use

### Compilation:

    make

### Reinstalliation

    make reinstall

### Uninstalliation

    make uninstall

## Supported flags

|Flag|Description|
|----|------------------------------------------------------------------------|
|```@```|Display extended attribute keys and sizes in long (```-l```) output.|
|```1```|The numeric digit ```one```. Force output to be one entry per line. This is the default when output is not to a terminal.|
|```A```|List all entries except for ```.``` and ```..```.|
|```a```|Include directory entries whose names begin with a dot (```.```).|
|```C```|Force multi-column output; this is the default when output is to a terminal.|
|```c```|Use time when file status was last changed for sorting (```-t```) or long printing (```-l```).|
|```F```|Display a slash (```/```) immediately after each pathname that is a directory, an asterisk (```*```) after each that is executable, an at sign(```@```) after each symbolic link, an equals sign (```=```) after each socket, a percent sign (```%```) after each whiteout, and a vertical bar (```|```)after each that is a FIFO.|
|```f```|Output is not sorted. This option turns on the ```-a``` option.|
|```G```|Enable colorized output.|
|```g```|Used to display the group name in the long (```-l```) format output (the owner name is suppressed).|
|```h```|When used with the ```-l``` option, use unit suffixes: Byte, Kilobyte, Megabyte, Gigabyte, Terabyte and Petabyte in order to reduce the number of digits to three or less using base 2 for sizes.|
|```i```|For each file, print the file's file serial number (inode number).|
|```l```|The lowercase letter ```ell```. List in long format. If the output is to a terminal, a total sum for all the file sizes is output on a line before  the long listing.|
|```m```|Stream output format; list files across the page, separated by   commas.|
|```n```|Display user and group IDs numerically, rather than converting to a user or group name in a long (```-l```) output.  This option turns on the ```-l``` option.|
|```o```|List in long format, but omit the group id.|
|```p```|Write a slash (```/```) after each filename if that file is a  directory.|
|```R```|Recursively list subdirectories encountered.|
|```r```|Reverse the order of the sort to get reverse lexicographical order or the oldest entries first (or largest files last, if combined with sort by size.|
|```S```|Sort files by size.|
|```T```|When used with the ```-l``` (lowercase letter ```ell```) option, display complete time information for the file, including month, day, hour, minute, second, and year.|
|```t```|Sort by time modified (most recently modified first) before sorting  the operands by lexicographical order.|
|```U```|Use time of file creation, instead of last modification for sorting  (```-t```) or long output (```-l```).|
|```u```|Use time of last access, instead of last modification of the file for sorting (```-t```) or long printing (```-l```).|
|```x```|The same as ```-C```, except that the multi-column output is produced with entries sorted across, rather than down, the columns.|

## License

Collision is an open-sourced software licensed under the [MIT license](LICENSE.md).
