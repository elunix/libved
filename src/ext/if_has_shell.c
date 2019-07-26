/* this unit is no guarded */

#include "../modules/proc/proc.c"

private int proc_output_to_stdout (buf_t *this, FILE *fp) {
  (void) this;
  char *line = NULL;
  size_t len = 0;
  while (-1 isnot getline (&line, &len, fp))
    fprintf (stdout, "%s\r", line);
  ifnot (NULL is line) free (line);
  return 0;
}

private int my_ed_sh_popen (ed_t *ed, buf_t *buf, char *com,
  int redir_stdout, int redir_stderr, int (*read_cb) (buf_t *, FILE *fp)) {
  int retval = NOTOK;
  proc_t *this = proc_new ();
  $my(read_stderr) =  redir_stderr;
  $my(read_stdout) = 1;
  $my(dup_stdin) = 0;
  $my(buf) = buf;
  ifnot (NULL is read_cb)
    $my(read) = read_cb;
  else
    if (redir_stdout)
      $my(read) = My(Buf).read.from_fp;
    else
      $my(read) = proc_output_to_stdout;

  proc_parse (this, com);
  term_t *term = Ed.get.term (ed);

  ifnot (redir_stdout)
    My(Term).reset (term);

  if (NOTOK is proc_open (this)) goto theend;
  retval = proc_read (this);
  proc_wait (this);

theend:
  ifnot (redir_stdout) {
    My(Term).set_mode (term, 'r');
    My(Input).get (term);
    My(Term).set (term);
  }

  proc_free (this);
  win_t *w = Ed.get.current_win (ed);
  int idx = My(Win).get.current_buf_idx (w);
  My(Win).set.current_buf (w, idx);
  My(Win).draw (w);
  return retval;
}

/*
#ifdef HAS_SHELL_COMMANDS
  Ed.sh.popen = my_ed_sh_popen;
#endif
 */