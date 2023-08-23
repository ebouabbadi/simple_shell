#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include "struct.h"

#define SPC ' '
#define OUTR '>'
#define APND ">>"
#define INR '<'
#define HRDC "<<"
#define S_QT '\''
#define D_QT '\"'
#define SNL ""

enum e_mini
{
	T_SPACE = 10,
	T_REDOUT,
	T_HEREDOC,
	T_REDINP,
	T_REDAPND,
	T_MOT,
	T_PIPE,
};

t_global g_global;

int main(int ac, char **av, char **envp);

int redirections(t_mini *lst);
int verification33(char c);
void expend_inside_herdoc(int fd, char *inpt);
void command_make(t_mini *lst, int len);
t_list *heredoc(t_mini *lst, t_list *node);
t_list *heredoc_handling(t_list *node, int fd);
int execution(t_mini **big_stack, t_env **envs);
char *comd_existe(t_mini *lst);
void check_if_cmd_builtins_and_run_intside(t_mini *lst, t_env **envs);
void check_if_cmd_builtins_and_run_outside(t_mini *lst, t_env **envs);
void wait_and_return_value_of_waitpid(t_mini *lst);
char *searching_for_cmd(t_mini *lst);
void ft_pipe(t_mini *lst);
void close_pipe_in_main_process(t_mini *lst);
void pipe_control(t_mini *lst);
char **extract_env(t_env **envs);
int len_(t_env **envs);
int lst_size(t_mini **stack);
void ft_unlink(t_mini **big_stack);
int if_cmd_in_builtins(t_mini *lst);
int len__(t_env **envs);
int if_number2(char *val);
void add_to_trash(void *ptr);
char *my_ft_strdup(const char *s1);
char *my_ft_substr(char const *s, unsigned int start, size_t len);
void add_to_list_env(t_env *lst, t_env **env);
void affich_env(t_env **stack);
t_env **ft_env(char **envp);
char *search_in_env(t_env **envs, char *variable);
void creat_env(t_env **stack, char *name, char *val);
int if_number(char *val);
void ft_export(t_mini *lst);
void affich_export(t_env **envs);
void add_to_env(char *variable, char *valleur, t_env **envs);
int if_variable_exist(char *variable, char *valleur, int flag, int append);
int if_not_a_valid_identifier(char *variable);
char *find_value2(char *cmd);
char *find_value1(char *cmd);
void ft_unset(t_env **envs, t_mini *lst);
void ft_cd(t_env **envs, char **cmd, int size);
void modif_pwd_in_env(t_env **envs);
char *search_in_env(t_env **envs, char *variable);
void modif_oldpwd_in_env(t_env **envs);
void if_cd_only2(int size, char *str);
void if_cd_and_argument2(char **cmd, int size, int *flag);
void if_cd_and_minus3(int size);
void if_cd_and_minus2(void);
void home_not_set(void);
void ft_pwd(void);
void ft_exit(t_mini *lst);
void ft_echo(t_mini *lst);
void fanc_aplic(int status);
int get_c(void);
void msg_perror(char *str, int case_);
void msg_error_exprt_unst(char *str, char *msg);
void msg_error_cd(char *msg);
t_mini **parsing(char *line1);
void line_handling(char *line, t_list **stack);
int pipe_handling(int i, t_list **stack);
int dq_handling(int i, t_list **stack, int start, char *line);
int sq_handling(int i, t_list **stack, int start, char *line);
int redc_handling(int i, t_list **stack, char *line);
int space_handlinge(int i, t_list **stack, int start, char *line);
void ft_lstadd_back(t_list **lst, t_list *new);
t_list *ft_lstlast(t_list *lst);
t_list *ft_lstnew(void *content);
void lst_add_big_stack(t_mini **big_stack, t_list **stack);
void expend(t_list **stack, t_list **new_stack);
void tokenization(t_list **stack);
int ft_strcmp(char *s1, char *s2);
int check_quote(char *line);
void cancel_expend(t_list **stack);
void mark_expend(t_list **stack);
void ft_add1(t_list **new_stack, t_list *lst);
void ft_add2(t_list **new_stack, char *str, int token, int flag);
void free_tab(char **tab);
void free_stack(t_list **stack, int status);
void free_and_print(char *line, char *line1);
void free_big_stack(t_mini **stk);
int syntax_error(t_list **stack);
int syntax_error2(t_list **stack, t_list *lst);
char *expend_sq_dq(t_list *node);
char *expend_sq_dq_a(char *mot, char *str, int *i, int start);
char *expend_sq_dq_b(char *mot, char *str, int *i, int start);
int verification2(char c);
void *ft_malloc(size_t count, size_t size);
char *my_ft_strjoin(char const *s1, char const *s2, int flag1, int flag2);

#endif