#ifndef OPTIONS_H_INCLUDED
#define OPTIONS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct{
	int char_delay;
	int char_udelay;
	int use_usec_delay;
} options_t;

int parse_opts(options_t* opts_out, char** pos_args_out, int argc, char** argv);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // OPTIONS_H_INCLUDED
