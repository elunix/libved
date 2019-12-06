public ed_T *E;

#define Ed      E->self
#define Cstring E->Cstring.self
#define Ustring E->Ustring.self
#define Vstring E->Vstring.self
#define String  E->String.self
#define Rline   E->Rline.self
#define Error   E->Error.self
#define Vsys    E->Vsys.self
#define Venv    E->Venv.self
#define Term    E->Term.self
#define Input   E->Input.self
#define File    E->File.self
#define Path    E->Path.self
#define Buf     E->Buf.self
#define Win     E->Win.self
#define Msg     E->Msg.self
#define Dir     E->Dir.self
#define Re      E->Re.self

#define $myed E->current

mutable public void __alloc_error_handler__ (int, size_t, char *,
                                                 const char *, int);
private void sigwinch_handler (int sig);

struct argparse;
struct argparse_option;

typedef int argparse_callback (struct argparse *, const struct argparse_option *);
int argparse_help_cb(struct argparse *, const struct argparse_option *);

enum argparse_flag {
    ARGPARSE_STOP_AT_NON_OPTION = 1,
    SHORT_OPT_HAS_NO_DASH,
};

enum argparse_option_type {
    ARGPARSE_OPT_END,
    ARGPARSE_OPT_GROUP,
    ARGPARSE_OPT_BOOLEAN,
    ARGPARSE_OPT_BIT,
    ARGPARSE_OPT_INTEGER,
    ARGPARSE_OPT_FLOAT,
    ARGPARSE_OPT_STRING,
};

enum argparse_option_flags {
    OPT_NONEG = 1,
};

struct argparse_option {
    enum argparse_option_type type;
    const char short_name;
    const char *long_name;
    void *value;
    const char *help;
    argparse_callback *callback;
    intptr_t data;
    int flags;
};

struct argparse {
    const struct argparse_option *options;
    const char *const *usages;
    int flags;
    const char *description;
    const char *epilog;
    int argc;
    const char **argv;
    const char **out;
    int cpidx;
    const char *optvalue;
};

#define OPT_END()        { ARGPARSE_OPT_END, 0, NULL, NULL, 0, NULL, 0, 0 }
#define OPT_BOOLEAN(...) { ARGPARSE_OPT_BOOLEAN, __VA_ARGS__ }
#define OPT_BIT(...)     { ARGPARSE_OPT_BIT, __VA_ARGS__ }
#define OPT_INTEGER(...) { ARGPARSE_OPT_INTEGER, __VA_ARGS__ }
#define OPT_FLOAT(...)   { ARGPARSE_OPT_FLOAT, __VA_ARGS__ }
#define OPT_STRING(...)  { ARGPARSE_OPT_STRING, __VA_ARGS__ }
#define OPT_GROUP(h)     { ARGPARSE_OPT_GROUP, 0, NULL, NULL, h, NULL, 0, 0 }
#define OPT_HELP()       OPT_BOOLEAN('h', "help", NULL,                 \
                                     "show this help message and exit", \
                                     argparse_help_cb, 0, OPT_NONEG)

int argparse_init (struct argparse *, struct argparse_option *,
                                       const char *const *, int);
int argparse_parse (struct argparse *, int, const char **);

#if HAS_REGEXP
  private int ext_re_compile (regexp_t *);
  private int ext_re_exec (regexp_t *, char *, size_t);
  private string_t *ext_re_parse_substitute (regexp_t *, char *, char *);
#endif

#if HAS_SHELL
  private int ext_ed_sh_popen (ed_t *, buf_t *, char *, int, int, PopenRead_cb);
#endif

#if HAS_USER_EXTENSIONS
  private void __init_usr__ (ed_t *);
  private void __deinit_usr__ (ed_t *);
#endif

#if HAS_LOCAL_EXTENSIONS
  private void __init_local__ (ed_t *);
  private void __deinit_local__ (ed_t *);
#endif

private void __init_ext__ (Class (ed) *, ed_t *);
private void __deinit_ext__ (ed_t *);