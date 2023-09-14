# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    project.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicolas <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 09:12:08 by nicolas           #+#    #+#              #
#    Updated: 2023/08/07 16:45:38 by nserve           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Colors
NC="\033[0m"
BOLD="\033[1m"
ILINE="\033[3m"
ULINE="\033[4m"
GRAY="\033[90m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[93m"
CYAN="\033[96m"
BLUE="\033[34m"
MAGENTA="\033[35m"

# Repositories
if [ -d "../../lib" ]; then
	repo="../../"
elif [ -d "../../../lib" ]; then
	repo="../../../"
elif [ -d "../../../../lib" ]; then
	repo="../../../../"
elif [ -d "../../src/" ] && [ -d "../../inc/" ] && [ -f "../../Makefile" ]; then
	repo="../../"
elif [ -d "../src/" ] && [ -d "../inc/" ] && [ -f "../Makefile" ]; then
	repo="../"
elif [ -d "src/" ] && [ -f "Makefile" ]; then
	repo="./"
else
	repo="./"
	printf "${BOLD}${RED}You are not in a C project folder\n${NC}"
fi
assets_repo=$repo"assets/"
inc_repo=$repo"inc/"
src_repo=$repo"src/"
lib_repo=$repo"lib/"
tests_repo=$src_repo"unit_tests/"
bin_repo=$repo"bin/"

fatal_error() {
	if [ -z "$1" ]
	then
		message="fatal error"
	else
		message="$1"
	fi
	if [ -z "$2" ]
	then
		exit_status=1
	else
		exit_status=$2
	fi
	printf "${RED}$message${NC}\n"
	exit $exit_status
}

# Check bash functions
commands_needed=("sleep" "dirname" "basename" "realpath" "ctags" "touch" "chmod" "mkdir" "mv" "make" "awk" "grep" "sed" "find" "cat")
for command_needed in ${commands_needed[@]}; do
	command -v $command_needed > /dev/null 2>&1 || fatal_error "${BOLD}$command_needed${NC} command not installed... Aborting."
done

#Check valgrind is installed
LEAKS=1
MEMLEAKS=""
LEAK_RETURN=240
if ! command -v valgrind > /dev/null 2>&1
then
	printf "${YELLOW}valgrind is not installed. Memory leaks detection is not enabled...${NC}\n"
	LEAKS=0
else
	if [ $LEAKS -gt 0 ]
	then
		MEMLEAKS="valgrind --leak-check=full --show-leak-kinds=all --undef-value-errors=no --error-exitcode=$LEAK_RETURN --errors-for-leak-kinds=all"
	fi
fi

# Help messages
help_run="\n
\n
>> Write your tests into ./unit_tests/ and run with -r\n
\n
--------------------------------------------------------------------\n
### TEST FILES :\n
--------------------------------------------------------------------\n
Tests files should be named \"TESTER_{realname}.c\"\n\n
You can create one from a template using the -c [filename] command.\n\n
If your tests requires depencies in other files, you need to add a\n
comment like:\n\n
\t//DEPENDENCIES: file.c file1.c file2.c\n\n
The comment can be anywhere in the testfile.\n\n
--------------------------------------------------------------------\n
### TESTS FUNCTIONS :\n
--------------------------------------------------------------------\n
Tests functions should have a prototype like this :\n\n
\tint\tT_{name}(void);\n\n
There may be several test functions in one single test file.\n\n
Return value :\n
--------------\n
The return value is 0 if the test passes succesfully or anything\n
else if not.\n
Functions are supposed to be executed in the same order than in the\n
file, but this is not garanteed.\n
--------------------------:------------------------------------------\n
### SHELL TEST FILES :\n
--------------------------------------------------------------------\n
Shell tests files should be named \"SHELL_{realname}.sh\"\n\n
Be careful to have the exec right (chmod +x <file>)\n
You can create one from a template using the -s [filename] command.\n
Exec rights will be automaticly granted.\n\n
Anything written (for example with echo) will be displayed in a\n
single line. Use '\\\\n' to line return, as if you really wanted to\n
print '\\\\n'."

help_init="Use -i to initialize the repo\n"

# Get functions
get_file_name() {
	echo $(basename $1) | sed -e "s/TESTER_//g" -e "s/MAIN_//g" -e "s/SHELL_//g"
}

get_test_name() {
	echo "TESTER_"$(basename $1)
}

get_shell_name() {
	echo "SHELL_"$(basename $(get_file_name $1) .c).sh
}

get_main_name() {
	echo "MAIN_"$(basename $(get_file_name $1))
}

# Gen functions
gen_project_template() {
	if ! [ -d $assets_repo ]; then
		mkdir $assets_repo
		echo -e "${ILINE}${GRAY}Repository has been created for: ${BOLD}${GREEN}assets/${NC}"
	else
		echo -e "${ILINE}${GRAY}Repository already exisiting for: ${BOLD}${YELLOW}assets/${NC}"
	fi
	if ! [ -d $inc_repo ]; then
		mkdir $inc_repo
		echo -e "${ILINE}${GRAY}Repository has been created for: ${BOLD}${GREEN}inc/${NC}"
	else
		echo -e "${ILINE}${GRAY}Repository already exisiting for: ${BOLD}${YELLOW}inc/${NC}"
	fi
	if ! [ -d $lib_repo ]; then
		mkdir $lib_repo
		echo -e "${ILINE}${GRAY}Repository has been created for: ${BOLD}${GREEN}lib/${NC}"
	else
		echo -e "${ILINE}${GRAY}Repository already exisiting for: ${BOLD}${YELLOW}lib/${NC}"
	fi
	if ! [ -d $src_repo ]; then
		mkdir $src_repo
		echo -e "${ILINE}${GRAY}Repository has been created for: ${BOLD}${GREEN}src/${NC}"
	else
		echo -e "${ILINE}${GRAY}Repository already exisiting for: ${BOLD}${YELLOW}src/${NC}"
	fi
	if ! [ -d $tests_repo ]; then
		mkdir $tests_repo
		echo -e "${ILINE}${GRAY}Repository has been created for: ${BOLD}${GREEN}src/unit_tests/${NC}"
	else
		echo -e "${ILINE}${GRAY}Repository already exisiting for: ${BOLD}${YELLOW}src/unit_tests/${NC}"
	fi
}

gen_gitignore() {
	if ! [ -f $repo.gitignore ]  || ! $(grep -q "obj\|obj/\*\*" "$repo.gitignore"); then
		echo -e "obj\nobj/**" >> $repo.gitignore
	fi
	if ! [ -f $repo.gitignore ]  || ! $(grep -q "outs\|outs/\*\*" "$repo.gitignore"); then
		echo -e "outs\nouts/**" >> $repo.gitignore
	fi
	if ! [ -f $repo.gitignore ]  || ! $(grep -q "bin\|bin/\*\*" "$repo.gitignore"); then
		echo -e "bin\nbin/**" >> $repo.gitignore
	fi
	if ! [ -f $repo.gitignore ]  || ! $(grep -q "lib/libft/obj\|lib/libft/obj/\*\*" "$repo.gitignore"); then
		echo -e "lib/libft/obj\nlib/libft/obj/**" >> $repo.gitignore
	fi
	if ! [ -f $repo.gitignore ]  || ! $(grep -q "lib/libft/libft.a" "$repo.gitignore"); then
		echo -e "lib/libft/libft.a" >> $repo.gitignore
	fi
	if ! [ -f $repo.gitignore ]  || ! $(grep -q ".vimspector.json" "$repo.gitignore"); then
		echo -e ".vimspector.json" >> $repo.gitignore
	fi
}

gen_source_template() {
	echo -e "#include \"$(echo $1 | sed "s/\.c/\.h/")\"" >> $src_repo$1
	echo -e "\n" >> $src_repo$1
	vim + -c"Stdheader" $src_repo$1  #-c"wq"
}

gen_header_template() {
	upperstr=$(echo $2 | tr '[:lower:]' '[:upper:]' | sed "s/\./_/")
	includes=$(find $inc_repo -name "*.h")
echo "#ifndef $upperstr
# define $upperstr

$(for include in $includes; do
	echo -e "# include \"$(basename $include)\""
done)

$(ctags -xu --fields=nP $src_repo$1 | grep -v "#define" | sed -e "s/^.*\.c\ *//g" -e "s/$/;/g" -e "s/^static.*//g")

#endif" >> $src_repo$2
	vim + -c"Stdheader" $src_repo$2 #-c"wq"
}

# if I want to extract define from source file ?
#$(ctags -xu --fields=nP $src_repo$1 | grep -e "#define" | sed -e "s/^.*\.c\ *//g" -e "s/$/;/g" -e "s/^static.*//g" -e "s/^#define/# define/g")

gen_test_template() {
new_file_name=$(get_test_name $1)
fonctions="$(ctags -xu --fields=nP $src_repo$1 | sed -e "s/^.*\.c\ *//g" -e "s/^static.*//g" -e "s/(.*)/()/g" -e "s/()//g" -e "s/.*\ //g" -e "s/^\**//g")"

echo "
// TEST FILE FOR $1
// Generated with the project generator utility

// Write your dependencies after the :
// do not uncomment
//DEPENDENCIES:

#include <stdio.h> // do not remove please

$(ctags -xu --fields=nP $src_repo$1 | sed -e "s/^.*\.c\ *//g" -e "s/$/;/g" -e "s/^static.*//g")
" > $tests_repo$new_file_name

for i in $fonctions; do
	echo "
// Autogenerated test function for $i
int	T_$i(void)
{
	printf("\"\\033[90m\""); // start of info display
	if ($i())
		return (printf("\"\\033[0m\""), 1);			// the test does not, displays error code
	printf("\"\\033[0m\""); // end of info display
		return (0);			// the test passes

}" >> $tests_repo$new_file_name
done
}

gen_shell_template() {
new_file_name=$(get_shell_name $1)
fonctions="$(ctags -xu --fields=nP $src_repo$1 | sed -e "s/^.*\.c\ *//g" -e "s/^static.*//g" -e "s/(.*)/()/g" -e "s/()//g" -e "s/.*\ //g" -e "s/^\**//g")"

echo "#!/bin/bash
vrai=\"${BOLD}${GREEN} OK ${NC}\"	# OK with some color
faux=\"${BOLD}${RED} KO ${NC}\"	# KO with different color
if [ \$(basename \$(realpath .)) = \"test_gen\" ]; then		# defines the work repo
	repo=\"../\"
else
	repo=\"./\"
fi
tests_repo=\$repo\"test_gen/\"								# defines the test repo (something with test_gen)
# if your script creates files, place them under \$tests_repo, and name them after TEMP_* so they will be automatically removed
# the \$1 arg is the .out of the main test, you can for example run it with valgrind
# uncomment the following line to do so :
# valgrind -s \$1


# Do stuff here


if [ 1 ]; then
	echo -e \$vrai				# the test passes
else
	echo -e \$faux				# the test doesnt
fi
"> $tests_repo$(get_shell_name $file)
}

# Do functions
do_test() {
	#check for include
	if ! [[ $(cat $1 | grep "#include <stdio\.h>") ]]; then
		echo "You removed the #include <stdio.h> -_-'"
		mv $1 $tests_repo"temp"
		echo "#include <stdio.h>" > $1
		cat $tests_repo"temp" >> $1
		rm $tests_repo"temp"
	fi
	sed -e "/.*main(/,/}\ \/\/EOAGM/d" -e "/.*main(/,/}/d" $1 > $tests_repo$(get_main_name $1)
	# EOAGM : End Of AutoGenerated Main
	vrai="${BOLD}${GREEN}OK${NC}"
	faux="${BOLD}${RED}KO${NC}"
	body=""
	fonctions="$(ctags -xu --fields=nP $1 | sed -e "s/^.*\.c\ *//g" | grep "T_.*" | sed -e "s/(.*)/()/g" -e "s/.*\ //g" -e "s/^\**//g")"
	for fonction in $fonctions; do
		body="$body$(echo -e "\n\t\tint\tv_$(echo $fonction | sed -e "s/^T_//g" -e "s/()//g") = $fonction;\n\t\tprintf(\"\t\033[1mTest for %s : %s (%d)\\\\n\", \"$(echo $fonction | sed "s/^T_//g")\", v_$(echo $fonction | sed -e "s/^T_//g" -e "s/()//g") ? \"$faux\" : \"$vrai\", v_$(echo $fonction | sed -e "s/^T_//g" -e "s/()//g"));")"
	done
	main="
	int	main(void)
	{$body
	}//EOAGM"
	edited=$(cat $tests_repo$(get_main_name $1))$main
	echo "$edited" > $tests_repo$(get_main_name $1)
	#Compilation
	compilation_logs="$(make -C $repo $bin_repo$(echo $(get_main_name $1) | sed "s/\.c/.out/g") 2>&1 | grep -v "make" | grep -v "Compiling"  | grep -v "compiled!" | grep -v "Norminette" | grep -v "Error:")"
	if [[ $compilation_logs ]]; then
		echo -e "${BOLD}${RED}ERRORS DURING COMPILATION${NC}"
		echo -e "$compilation_logs\n"
	else
		if ! [ $2 ]; then
			#sanitizer_logs=$($bin_repo$(echo $(get_main_name $1) | sed -e "s/\.c/.out/g") 2>&1)
			#if [[ $sanitizer_logs ]]; then
			#	echo -e "${BOLD}${RED}LEAK ERRORS DURING EXECUTION${NC}"
			#	echo -e "$sanitizer_logs"
			#	echo -e "=================================================================\n"
			#else
				$bin_repo$(echo $(get_main_name $1) | sed -e "s/\.c/.out/g")
			#fi
		fi
	fi
	if ! [ $2 ]; then
		$(do_shell_test $1 $(echo $fonction | sed "s/^T_//g"))
	fi
}

do_shell_test() {
	find $tests_repo -name "TEMP_*" -exec chmod a+rwx {} ";"
	if [ -f $tests_repo$(get_shell_name $1) ]; then
		len=$(($(echo -n $2 | wc -c)-9))
		if [[ $len < 0 ]]; then len=0; fi
		echo -en "\tShell script tests :$(printf "%$len.s" " ") "
		echo -e $($tests_repo$(get_shell_name $1) $tests_repo$(echo $(get_main_name $1) | sed -e "s/\.c/.out/g") | tr "\n" " ")
	fi
}

do_clean() {
	if ! [ $1 ]; then
		find $tests_repo \( -name "TEMP_*" -o -name "MAIN*\.c" -o -name "*\.out" \) -delete
		find $bin_repo \( -name "*\.out" \) -delete
		rm -rf $bin_repo
	else
		find $tests_repo -name "TEMP_*" -delete
	fi
}

# Script
while getopts "aidmlchusrg" opt; do
	case $opt in
		a)
			if [ -d $src_repo ] || [ -f $repo"Makefile" ]; then
				echo -e $help_run | less
			else
				echo -e $help_init
			fi
			;;
		i)
			project_repo=$(basename $(realpath .))
			if [ $repo != "./" ] || [[ $project_repo =~ ^(assets|src|inc|lib|obj|bin|outs|unit_tests)$ ]]; then
				echo -e "${ILINE}${GRAY}Your can't initiate a new project inside an existing one.\nList of forbidden repository name: ${BOLD}${BLUE}assets|inc|lib|src|unit_tests|obj|bin|outs${NC}."
				echo -e "Project can't be initiated in repository: \t${BOLD}${RED}$project_repo/${NC}, see -h"
			elif [ -d $assets_repo ] && [ -d $inc_repo ] && [ -d $src_repo ] && [ -d $lib_repo ] && [ -d $tests_repo ]; then
				gen_gitignore
				echo -e "Project already initialized for repository: ${BOLD}${YELLOW}$project_repo${NC}\n"
				ls -lA --color | grep "^d" && ls -lA --color | grep -v "^d" | grep -v "total"
			else
				gen_project_template
				gen_gitignore
				echo -e "Project succesfully initialized for repository: ${BOLD}${GREEN}$project_repo${NC}\n"
			fi
			;;
		d)
			echo "debug"
			;;
		m)
			echo "Makefile"
			;;
		l)
			echo "library"
			;;
		c)
			for file in $*; do
				if [ $file = "-c" ]; then
					continue
				fi
				if [ $(echo $file | grep "\.c") ]; then
					if [ -f $src_repo$file ]; then
						echo -e "File ${BOLD}${YELLOW}$src_repo$file${NC} already exists. Delete first if you want to create a new one"
					else
						gen_source_template $file
						echo -e "Source file generated for ${BOLD}${GREEN}$file${NC}"
					fi
				else
					echo -e "${BOLD}Wrong input${NC} :\t${BOLD}${RED}$file${NC}"
				fi
			done
			;;
		h)
			for file in $*; do
				if [ $file = "-h" ]; then
					continue
				fi
				file=$(basename $file)
				if [ $(echo $file | grep "\.c") ] && [ -f $src_repo$file ]; then
					header=$(echo $file | sed "s/\.c/\.h/")
					if [ -f $src_repo$header ]; then
						rm $src_repo$header
						gen_header_template $file $header
						echo -e "File ${BOLD}${YELLOW}$src_repo$header${NC} already exists. File has been updated"
					else
						gen_header_template $file $header
						echo -e "Header file generated for ${BOLD}${GREEN}$file${NC}"
					fi
				else
					echo -e "${BOLD}Wrong input${NC} :\t${BOLD}${RED}$file${NC}"
				fi
			done
			;;
		u)
			for file in $*; do
				if [ $file = "-u" ]; then
					continue
				fi
				if [ $(echo $file | grep "\.c") ] && [ -f $src_repo$(get_file_name $file) ]; then
					if [ -f $tests_repo$(get_test_name $file) ]; then
						echo -e "File ${BOLD}${YELLOW}$tests_repo$(get_test_name $file)${NC} already exists. Delete first if you want to create a new one"
					else
						gen_test_template $file
						echo -e "Test template generated for ${BOLD}${YELLOW}$(get_file_name $file)${NC}"
					fi
				else
					echo -e "${BOLD}${RED}Wrong input${NC} :\t\t${BOLD}${YELLOW}$(get_file_name $file)${NC}"
				fi
			done
			;;
		s)
			for file in $*; do
				if [ $file = "-s" ]; then
					continue
				fi
				if [ $(echo $file | grep "\.c") ] && [ -f $src_repo$(get_file_name $file) ]; then
					if [ -f $tests_repo$(get_shell_name $file) ]; then
						echo -e "File ${BOLD}${YELLOW}$tests_repo$(get_shell_name $file)${NC} already exists. Delete first if you want to create a new one"
					else
						gen_shell_template $file
						chmod +x $tests_repo$(get_shell_name $file)
						echo -e "Shell template generated for ${BOLD}${YELLOW}$(get_file_name $file)${NC}"
					fi
				else
					echo -e "${BOLD}${RED}Wrong input${NC} :\t\t${BOLD}${YELLOW}$(get_file_name $file)${NC}"
				fi
			done
			;;
		r)
			if [ $2 ]; then
				files=$*
			else
				files=$(find . -name "TESTER_*\.c")
			fi
			for file in $files; do
				if [ $file = "-r" ]; then
					continue
				fi
				if [ $(echo $file | grep "TESTER_.*\.c") ] && [ -f $tests_repo$(basename $file) ]; then
					to_test=$tests_repo$(basename $file)
				else
					if [ $(echo $(get_test_name $file) | grep "\.c") ] && [ -f $tests_repo$(get_test_name $file) ]; then
						to_test=$tests_repo$(get_test_name $file)
					else
						echo -e "${BOLD}${RED}No testfile found${NC} :\t\t${BOLD}${YELLOW}$(get_file_name $file)${NC}"
						continue
					fi
				fi
				echo -e "\n================================================================="
				echo -e "Processing tests for ${BOLD}${YELLOW}$(get_file_name $file)${NC}"
				echo -e "=================================================================\n"
				do_test $to_test
				do_clean
			done
				echo -e "\n================================================================="
			;;
		g)
			if [ $2 ]; then
				files=$*
			else
				files=$(find . -name "TESTER_*\.c")
			fi
			for file in $files; do
				if [ $file = "-g" ]; then
					continue
				fi
				if [ $(echo $file | grep "TESTER_.*\.c") ] && [ -f $tests_repo$(basename $file) ]; then
					to_test=$tests_repo$(basename $file)
				else
					if [ $(echo $(get_test_name $file) | grep "\.c") ] && [ -f $tests_repo$(get_test_name $file) ]; then
						to_test=$tests_repo$(get_test_name $file)
					else
						echo -e "${BOLD}${RED}No testfile found${NC} :\t\t${BOLD}${YELLOW}$(get_file_name $file)${NC}"
						continue
					fi
				fi
				echo -e "\n================================================================="
				echo -e "Processing tests for ${BOLD}${YELLOW}$(get_file_name $file)${NC}"
				echo -e "=================================================================\n"
				do_test $to_test 1
				do_clean 1
			done
				echo -e "\n================================================================="
			;;
	esac
done
