# void	load_history(void)
### edited
Peut être remplacer le substr par juste remplacer le \n par \0, plus économe en mémoire et moins de risque de malloc...

# void	rpel_loop(t_myshell *shell)
### edited
Pourquoi un strcmp a la place du cmdline[0] = '\n' ?

# int	tok_buf_init(t_source *src)
init the buffer, is 1024 reused in the code ? if so maybe use a macro or a global static const.
all the buffer is set to '\0'

# int	entry_add(t_history *origin, char *str)
## critical
### edited
avec t_myentry *to_add, malloc(sizeof (*to_add)) serait pas equivalent a malloc(sizeof(to_add)) ?
when accesing line 25, to_add is always NULL
*origin never updated
to_add never added to previous one !!

