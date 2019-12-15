/* A simple utility that utilizes the library by linking against. */

/* Some notes below might be outdated. The interface (the actual
 * structure) won't change much, but the way it does things might.
 * The way that someone access the structure is not yet guaranteed.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <sys/stat.h>
#include <errno.h>

#include <libved.h>
#include <libved+.h>

static const char *const usage[] = {
    "veda [options] [filename]",
    NULL,
};

int main (int argc, char **argv) {
  /* I do not know the way to read from stdin and at the same time to
   * initialize and use the terminal state, when we are the end of the pipe */
  if (0 is isatty (fileno (stdout)) or 0 is isatty (fileno (stdin))) {
    tostderr ("Not a controlled terminal\n");
    exit (1);
  }

  setlocale (LC_ALL, "");

  AllocErrorHandler = __alloc_error_handler__;

  char *ftype = NULL;
  int filetype = FTYPE_DEFAULT;
  int linenr = 0;
  int column = 1;

  struct argparse_option options[] = {
    OPT_HELP (),
    OPT_GROUP("Options:"),
    OPT_INTEGER('+', "line-nr", &linenr, "start at line number", NULL, 0, SHORT_OPT_HAS_NO_DASH),
    OPT_INTEGER(0, "column", &column, "set pointer at column", NULL, 0, 0),
    OPT_STRING(0, "ftype", &ftype, "set the file type", NULL, 0, 0),
    OPT_END(),
  };

  struct argparse argparse;
  argparse_init (&argparse, options, usage, 0);
  argc = argparse_parse (&argparse, argc, (const char **) argv);

  if (argc is -1) return 1;

  if (NULL is (E = __init_ed__ ()))
    return 1;

  ed_t *this = Ed.new (E, 1);

  __init_ext__ (E, this);

#ifdef HAS_HISTORY
  Ed.history.read (this, VED_DATA_DIR);
#endif

  filetype = Ed.syn.get_ftype_idx (this, ftype);

/* at the begining at least a win_t type is allocated */
  win_t *w = Ed.get.current_win (this);

  ifnot (argc) {
    /* just create a new empty buffer and append it to its
     * parent win_t to the frame zero */
    buf_t *buf = Win.buf.new (w, BUF_INIT_QUAL());
    Win.append_buf (w, buf);
  } else
    /* else create a new buffer for every file in the argvlist */
    for (int i = 0; i < argc; i++) {
      buf_t *buf = Win.buf.new (w, QUAL(BUF_INIT,
        .fname = argv[i],
        .ftype = filetype,
        .at_frame = FIRST_FRAME,
        .at_linenr = linenr,
        .at_column = column));

      Win.append_buf (w, buf);
    }

  /* set the first indexed name in the argvlist, as current */
  Win.set.current_buf (w, 0, DRAW);

  int retval = 0;
  signal (SIGWINCH, sigwinch_handler);

  for (;;) {
    buf_t *buf = Ed.get.current_buf (this);
    /* main loop */
    retval = Ed.main (this, buf);

    /* here the user suspended its editor instance, with CTRL-j */
    if (Ed.get.state (this) & ED_SUSPENDED) {
      if (E->num_items is 1) {
        /* as an example, we simply create another independed instance */
        this = Ed.new (E, 1);
        w = Ed.get.current_win (this);
        buf = Win.buf.new (w, BUF_INIT_QUAL());
        Win.append_buf (w, buf);
        Win.set.current_buf (w, 0, DRAW);
      } else {
        /* else jump to the next or prev */
        this = Ed.get.prev (this);
      }
    } else break;
  }

#ifdef HAS_HISTORY
  Ed.history.write (this, VED_DATA_DIR);
#endif

  __deinit_ext__ (this);
  __deinit_ed__ (E);

/* the end */
  return retval;
}
