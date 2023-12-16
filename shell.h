#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
<<<<<<< HEAD
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
=======
#include <stdarg.h>
#include <signal.h>

/* MACROS */
#define SHELL_RUNNING 1
#define BUFFER_SIZE 1024


/* string manipulation functions */
char **_strtok(const char *str, char *delim);
int countwords(const char *str);
char *copyword(const char *str, int start, int end);
char *_strchr(char *s, char c);
int _strncmp(const char *str1, const char *str2, size_t n);
int _strlen(const char *s);
char *_strdup(char *str);
int _isalpha(int c);
char *_strncpy(char *dest, const char *src, int n);
int _strcmp(char *s1, char *s2);
ssize_t _getline(char **line, size_t *n, int fd);
int resize_buffer(char **lineptr, size_t *buffer_size, size_t total_read);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void *_memcpy(void *dest, const void *src, size_t n);
void prompt(void);
void setup_signal_handler(void);
void signal_handler(int signal_number);


/* environment and PATH handlers */

extern char **environ;

/**
 * struct _path - the entry point.
 * Decription - epresents a node in a linked list for the PATH variable.
 * @pathname: A pointer to a string representing a directory path.
 * @next: A pointer to the next node in the linked list.
>>>>>>> 2e545be6a7ad2381ff9082119b909caf4ecadcca
 */
typedef struct _path
{
<<<<<<< HEAD
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
=======
	char *pathname;
	struct _path *next;
} path_t;

path_t *build_path_list(path_t **head);
void print_path_list(path_t *list);
void free_path_list(path_t **list);

char *_getenv(const char *name);
char *v_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void _printenv(void);

/**
 * struct shell - the entry point.
 * Description - represents the state of a simple shell.
 * @user_input: The input command string provided by the user.
 * @prog_name: The name of the shell program.
 * @exit_code: The exit code of the last executed command.
 * @command_array: Array of strings representing the parsed commands.
 * @tokenized_commands: an array of tokenized versions of each command
 * @tokens: Array of strings representing individual tokens of a cmd.
 * @token: A single token within the array of tokens.
 * @exit_status: The exit status of the shell.
 * @cmd_count: The count of executed commands.
 * @path_list: Linked list of paths for command execution.
>>>>>>> 2e545be6a7ad2381ff9082119b909caf4ecadcca
 */
typedef struct shell
{
<<<<<<< HEAD
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_builtin1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toem_getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
=======
	char *user_input;
	char *prog_name;
	int exit_code;
	char **command_array;
	char **tokenized_commands;
	char **tokens;
	char *token;
	const char *exit_status;
	size_t cmd_count;
	path_t *path_list;
} shell_t;

shell_t *initialise_shell(void);
void free_up(const char *format, ...);
int exit_shell(shell_t *msh, void (*func)(const char *format, ...));
void handle_empty_prompt(ssize_t bytes_read, shell_t *lsh);
void execute_file_as_input(char *filename, shell_t *msh);

/* command execution and parsing funcs. */
int parse_input(shell_t *lsh);
int execute_command(const char *command, shell_t *lsh);
int execute_tokens(shell_t *lsh, size_t index);
int execute_with_path(shell_t *lsh);
int cmd_not_found(shell_t *lsh);
int parser(shell_t *lsh);
int execute_builtin(shell_t *lsh);
void aux_parser(shell_t *lsh, size_t index);
char *remove_comments(char *command);

/* error handling funcs */
void handle_error(const char *message);

/* custom memory deallocation */
void free_copyword(char *word);
void free_string(char ***string_array);
void _free(void **ptr);

#define safefree(p) _free((void **)&(p))

#endif /* SHELL_H */
>>>>>>> 2e545be6a7ad2381ff9082119b909caf4ecadcca
