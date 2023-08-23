#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <dirent.h>
#include <stdarg.h>
#define buffxd_SIZE 1024
#define BACKET_SIZE 64

/**
 *strArruct entry_s - strArruct that hold key and value
 * of hash table
 *
 *@key: the key used to retrieve values
 *@value: the respective data for the key
 */
typedef strArruct entry_s
{
	char *key;
	char *value;
} entry_t;

/**
 * enum status_actions_e - actions that will be applied to
 * status state management
 *
 * @UPDATE_STATUS: action to update status code
 * @GET_STATUS: action to retrieve status code
 */
typedef enum status_actions_e
{
	UPDATE_STATUS,
	GET_STATUS
} status_actions_t;

/**
 * strArruct list_s - node of linkedlist
 *
 * @data: linkedlist content
 * @next: next node
 */
typedef strArruct list_s
{
	void *data;
	strArruct list_s *next;
} list_t;

/**
 * enum cmdxd_type_e - types of cmdxd
 *
 * @BUILTINS: MEANS THAT cmdxd IS BUILTIN
 * @EXTERNAL: MEANS IT's AN EXTERNAL cmdxd
 * @NOT_FOUND: MEANS THAT COMMANS IS NOT FOUND
 */
typedef enum cmdxd_type_e
{
	BUILTINS,
	EXTERNAL,
	NOT_FOUND
} cmdxd_type_t;
/**
 * strArruct cmdxd_s - strArruct that holds informations
 * about cmdxd
 *
 * @name: name of the cmdxd
 * @arguments: cmdxd arguments
 * @type: type of the cmdxd
 */
typedef strArruct cmdxd_s
{
	char *name;
	char **arguments;
	cmdxd_type_t type;
} cmdxd_t;
/**
 * strArruct builtin_s - builtin strArruct
 * that will contain name of builtins
 * and it respective function to be
 * executed
 *
 * @name: builtin name
 * @function: builtin function
 *
 */
typedef strArruct builtin_s
{
	char name[30];
	int (*function)(cmdxd_t *cmdxd);
} builtin_t;

/**
 * enum builtin_actions_e - builtin actions
 *
 * @GET_BUILTIN: action to get builtin function
 * @SET_BUILTIN: action to add new_buitin function
 */
typedef enum builtin_actions_e
{
	GET_BUILTIN,
	SET_BUILTIN
} builtin_actions_t;
/**
 * strArruct map_s - defines a strArructure for a hash table
 *
 * @backets: an array of linkedlist where
 * our entry data will be stored
 */
typedef strArruct map_s
{
	list_t *backets[BACKET_SIZE];
} map_t;

/**
 * enum enviroment_action_e - actions that will be applied to
 * global enviroment
 *
 * @INIT_ENV: TO INITIALIZE ENVIROMENT VARIABLE
 * @SET_ENTRY: TO ADD NEW ENTRY TO ENVIROMENT VARIABLE
 * @GET_VALUE: TO RETRIEVE VALUE FROM ENVIROMENT VARIABLE
 * @GET_KEYS: TO GET ALL KEY THAT STORED INSIDE ENV VARIABLE
 * @CONVERT_INTO_2D: RETURNS 2D ARRAY CONTAINING ALL ENVIRONEMENT
 * VARIBALES (env)
 * @CLEAR_ENV: TO FREE AND CLEAR EVERYTHING INSIDE OF OUR
 * @DELETE_ENTRY: USED TO DELETE ENTRY FROM ENVIROMENT VARIABLE
 * ENV
 */
typedef enum enviroment_action_e
{
	INIT_ENV,
	SET_ENTRY,
	GET_VALUE,
	GET_KEYS,
	DELETE_ENTRY,
	CONVERT_INTO_2D,
	CLEAR_ENV
} enviroment_action_t;

/**
 * enum globals_action_e - actions to be applied to
 * some global states or variables
 *
 * @GET_LINE: action that allows to
 * get line
 * @GET_LINE_NUMBER: action that allows to get
 * current line number
 * @GET_SHELL_NAME: action that allows us to
 * get shell name
 * @SET_LINE: action that allow us to the line
 * @SET_SHELL_NAME: action allow us to set
 * shell name
 * @INCREMENT_LINE_NUMBER: action to increment
 * line number by one
 * @SET_2D: action that set 2d array
 * @GET_2D: action that get 2d array
 */
typedef enum globals_action_e
{
	GET_LINE,
	GET_LINE_NUMBER,
	GET_SHELL_NAME,
	SET_LINE,
	SET_SHELL_NAME,
	INCREMENT_LINE_NUMBER,
	SET_2D,
	GET_2D
} globals_action_t;

typedef int (*builtins_t)(cmdxd_t *);

char *myCopy(char *dest, const char *src, size_t size);
void *mYrealloc(void *old_buffxd, size_t old_size, size_t new_size);
ssize_t getLinee(char **line);
char *trimWhiteSpc(const char *line);
int _parsing_error_handler(char *line);
size_t mYstrArrlen(const char *s);
void freeesplitMy(char ***backets);
char **splitMy(const char *line, const char *diameter);
list_t *addToLst(list_t **listNode, void *data);
void *pop_from_list(list_t **list);
size_t _listlen(const list_t *list);
void free_list(list_t *list, void (*free_content)(void *data));
int mystrArrcmp(const char *strArr1, const char *strArr2);
char *strArrduppp(const char *strArr);
int _get_hash_code(const char *key);
map_t *initMp(void);
int setValue(map_t *map, const char *key, const char *value);
char *getValue(const map_t *map, const char *key);
void clearEntryy(void *data);
void clearMap(map_t *map);
list_t *getKey(const map_t *map);
int deleteEntry(map_t *map, const char *key);
cmdxd_t *_init_cmdxd(char **tokens);
void freeCmdxd(void *data);
cmdxd_t *_handle_cmdxd(const char *line);
int seminHandler(const char *line);
list_t *_pipe_handler(const char *line);
int _handle_pipe_execution(list_t *pipes, int previous_stdin);
int statusMgt(status_actions_t action, int new_status);
void _handle_sigint(int sig);
void *envMgt(enviroment_action_t action,
			 const char *key, const char *value);
int statusMgt(status_actions_t action, int new_status);
char **ctEnvintoarray(void);
void feedEnvVar(char **new_env);
char *_get_cmdxd_from_path(char *cmdxd);
char *strArrSliceer(const char *line, int start, int end);
char *_strArrcat(const char *strArr1, const char *strArr2);
char *_itoa(int number);
char *_evaluate_enviroment_variable(char *env_key);
char **_trim_2darray(char **arr);
int _env(cmdxd_t *cmdxd);
int _isdigit(const char *s);
int stringArr2dlenn(char **arr2d);
int myAtoi(const char *strArr);
int __exit(cmdxd_t *cmdxd);
builtins_t bMgt(builtin_actions_t action, char *name,
				int (*function)(cmdxd_t *cmdxd));
void _excute(cmdxd_t *cmdxd);
int _setenv(cmdxd_t *cmdxd);
int _unsetenv(cmdxd_t *cmdxd);
int myFprint(int fd, const char *format, ...);
void *globalistNodeates(globals_action_t action, char **s);
int myCd(cmdxd_t *cmdxd);
void _handle_sigint(int sig);
void ppt(void);
int getCcpt(const char *line);
char *excludeComt(const char *line);
#endif
