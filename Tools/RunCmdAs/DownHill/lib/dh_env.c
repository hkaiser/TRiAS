/*****************************************************************************
 *                                                                           *
 * DH_ENV.C                                                                 *
 *                                                                           *
 * Freely redistributable and modifiable.  Use at your own risk.             *
 *                                                                           *
 *****************************************************************************/
/*
 * HISTORY
 * 	Implement wrappers for getenv/setenv/unsetenv that emulate case-sensitive
 * 	environment variable names and the empty string as a valid value.
 * 	[1997/05/10  02:46:02  tbartley]
 */
#if !defined(lint) && !defined(_NOIDENT)
static const char* rcsid = "@(#)$RCSfile: dh_env.c,v $ $Revision: 1.1.2.2 $ (DOWNHILL) $Date: 1997/05/10 02:48:50 $";
#endif

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

/*
 * We need to call getenv ourselves so we undefine
 * our own hash define.
 */
#undef getenv

/*
 * In order to provide for mixes case environment variables
 * we maintain a shadow if the real environment and store
 * special encoding in the real environment.
 *
 * The following modifiers appearing in a real environment
 * variable name are interpreted as shown. The quoting
 * character is chosen as '_' as a legal environment variable
 * character.
 *      Real		Shadow
 *	__		_
 *	_L		all characters from here on are lower case
 *	_U		all characters from here on are upper case
 *
 * For example an environment variable project_name is represented
 * as _LPROJECT__NAME and the environment variable PROJECT_NAME is
 * represented as PROJECT__NAME (upper case is the default).
 *
 * The only value encoding done is:
 *	Real first characters	Value
 *	__			_
 *	_E			empty string
 *
 * Thus the value _foo_bar is encoded as __foo_bar and the empty
 * string is encoded as _E.
 */
typedef struct {
    char* shadow_name;
    char* shadow_value;
    char* real_assertion;
} shadow_env_t;

#define SHADOW_ALLOC_CHUNK 	  20

static shadow_env_t* shadow_env       = NULL;
static unsigned      shadow_used      = 0;
static unsigned      shadow_allocated = 0;

typedef enum { lower, upper } mangle_state_t;

static int mangle_name_length(const char* name)
{
    mangle_state_t state = upper;
    const char*           c;
    int   extras;
    int   length;

    extras = 0;
    length = 0;
    for (c = name; *c; ++c, ++length) {
	if (*c == '_') {
	    extras += 1;
	}
	else if (state == upper && islower(*c)) {
	    extras += 2;
	    state   = lower;
	}
	else if (state == lower && isupper(*c)) {
	    extras += 2;
	    state   = upper;
	}
    }
    
    return length + extras;
}

static void mangle_name(const char* name, char* mangled)
{
    mangle_state_t state = upper;
    const char* c;
    char*       m;

    for (c = name, m = mangled; *c; ++c) {
	if (*c == '_') {
	    *m++ = *c;
	    *m++ = *c;
	}
	else {
	    if (state == lower && isupper(*c)) {
	        *m++ = '_';
	        *m++ = 'U';
		state = upper;
	    }
	    else if (state == upper && islower(*c)) {
	        *m++ = '_';
	        *m++ = 'L';
		state = lower;
	    }
	    *m++ = *c;
	}
    }
    *m = '\0';
}    

static int mangle_value_length(const char* value)
{
    if (*value) {
	if (*value == '_') {
	    return strlen(value) + 1;
	}
	else {
	    return strlen(value);
	}
    }
    else {
	return 2;
    }
}

static void mangle_value(const char* value, char *mangled)
{
    if (*value == '\0') {
	strcpy(mangled, "_E");
    }
    else {
	if (*value == '_') {
	    *mangled++ = '_';
	}
	strcpy(mangled, value);
    }
}

static const char* demangle_value(const char* value)
{
    if (value[0] == '_') {
	switch(value[1]) {
	    case '_': return &value[1];
	    case 'E': return &value[2];
	    default:  return value;
	}
    }
    else {
	return value;
    }
}

static int demangle_name_length(const char* name)
{
    const char *c;
    mangle_state_t state = upper;
    int length;

    for (c = name, length = 0; *c; ++c) {
	if (*c == '_') {
	    ++c;
	    switch(toupper(*c)) {
	        case 'U': state = upper; break;
	        case 'L': state = lower; break;
	        default:  length += 2;   break;
	    }
	    ++c;
	}
	else {
	    ++length;
	}
    }
    return length;
}

static void demangle_name(const char* name, char* demangled)
{
    mangle_state_t state = upper;
    const char* c;
    char*       d;

    for (c = name, d = demangled; *c; ++c) {
	if (*c == '_') {
	    ++c;
	    switch(*c) {
	        case 'U': state = upper; continue;
	        case 'L': state = lower; continue;
	        default:  *d++ = '_';    break;
	    }
	}
	if (state == upper) *d++ = toupper(*c);
	else                *d++ = tolower(*c);
    }
}

static int new_chunk()
{
    shadow_env_t* new_shadow_env;

    shadow_allocated += SHADOW_ALLOC_CHUNK;
    
    new_shadow_env = realloc(shadow_env,
			     sizeof(shadow_env_t) * shadow_allocated);
    if (new_shadow_env == NULL) {
	return 0;
    }
    else {
	shadow_env = new_shadow_env;
	return 1;
    }
}

static shadow_env_t* getshadow(const char* name)
{
    unsigned i;
    int   shadow_length;
    char* mangled_name;
    char* shadow_name;
    char* mangled_value;
    char* real_assertion;
    char* unmangled_value;

    for (i = 0; i < shadow_used; ++i) {
	if (strcmp(name, shadow_env[i].shadow_name) == 0) {
	    return &shadow_env[i];
	}
    }
    
    shadow_length = mangle_name_length(name);
    if ((mangled_name = malloc(shadow_length + 1)) == NULL) {
	return NULL;
    }
    
    if (shadow_used == shadow_allocated) {
	if (!new_chunk()) {
	    free(mangled_name);
	    return NULL;
	}
    }
    if ((shadow_name = malloc(strlen(name)+1)) == NULL) {
	free(mangled_name);
	return NULL;
    }
    strcpy(shadow_name, name);
    shadow_env[shadow_used].shadow_name = shadow_name;

    mangle_name(name, mangled_name);
    if ((mangled_value = getenv(mangled_name)) == NULL) {
	/*
	 * If there's no mangled name try the unmangled name
	 */
	if ((unmangled_value = getenv(name)) == NULL) {
	    shadow_env[shadow_used].shadow_value = NULL;
	    real_assertion = realloc(mangled_name, shadow_length + 2);
	    if (real_assertion == NULL) {
		free(shadow_name);
		free(mangled_name);
		return NULL;
	    }
	    strcat(real_assertion, "=");
	    shadow_env[shadow_used].real_assertion = real_assertion;
	    return &shadow_env[shadow_used++];
	}
	else {
	    /*
	     * There is an unmangled version of the variable in the
	     * environment so we get it mangle it and set up a mangled
	     * version.
	     */
	    shadow_env[shadow_used].shadow_value = malloc(strlen(unmangled_value)+1);
	    if (shadow_env[shadow_used].shadow_value == NULL) {
		free(shadow_name);
		free(mangled_name);
		return NULL;
	    }
	    strcpy(shadow_env[shadow_used].shadow_value, unmangled_value);
	    
	    shadow_length += mangle_value_length(unmangled_value);
	    real_assertion = realloc(mangled_name, shadow_length + 2);
	    if (real_assertion == NULL) {
		free(shadow_name);
		free(mangled_name);
		free(shadow_env[shadow_used].shadow_value);
		return NULL;
	    }
	    shadow_env[shadow_used].real_assertion = real_assertion;
	    strcat(real_assertion, "=");
	    mangle_value(unmangled_value, strchr(real_assertion, '=')+1);
	    _putenv(real_assertion);
	    return &shadow_env[shadow_used++];
	}
    }
    else {
	shadow_length += strlen(mangled_value);
	real_assertion = realloc(mangled_name, shadow_length + 2);
	if (real_assertion == NULL) {
	    free(shadow_name);
	    free(mangled_name);
	    return NULL;
	}
	shadow_env[shadow_used].real_assertion = real_assertion;

	shadow_env[shadow_used].shadow_value = malloc(strlen(demangle_value(mangled_value)) + 1);
	if (shadow_env[shadow_used].shadow_value == NULL) {
	    free(shadow_name);
	    free(mangled_name);
	    return NULL;
	}
	strcat(shadow_env[shadow_used].real_assertion, "=");
	strcat(shadow_env[shadow_used].real_assertion, mangled_value);
	strcpy(shadow_env[shadow_used].shadow_value, demangle_value(mangled_value));
	return &shadow_env[shadow_used++];
    }
}
	
    
/*
 * setenv
 *
 * If rewrite is set, replace any current value.
 */
int
setenv(const char *name, const char *value, int rewrite)
{
    shadow_env_t* shadow;

    if ((shadow = getshadow(name)) == NULL) {
	return -1;
    }

    if (rewrite || !shadow->shadow_value) {
	char* new_value;
	char* new_assertion;
	int   mangled_value_length;
	int   mangled_name_length;

	new_value = realloc(shadow->shadow_value, strlen(value) + 1);
	if (new_value == NULL) {
	    return -1;
	}
	shadow->shadow_value = new_value;
	strcpy(shadow->shadow_value, value);

	mangled_name_length  = mangle_name_length(name);
	mangled_value_length = mangle_value_length(value);
	
	new_assertion = realloc(shadow->real_assertion,
				  mangled_name_length
				+ mangled_value_length
				+ 2);
	if (new_assertion == NULL) {
	    return -1;
	}
	shadow->real_assertion = new_assertion;
	
	mangle_name(name, shadow->real_assertion);
	strcpy(&shadow->real_assertion[mangled_name_length], "=");
	mangle_value(value, &shadow->real_assertion[mangled_name_length+1]);
	_putenv(shadow->real_assertion);
    }
    return 0;
}
    
void
unsetenv(const char *name)
{
    char* real_value;
    unsigned i;
    for (i = 0; i < shadow_used; ++i) {
	if (strcmp(name, shadow_env[i].shadow_name) == 0) {
	    break;
	}
    }
    
    if (i != shadow_used) {
	real_value = strchr(shadow_env[i].real_assertion, '=');
	if (real_value == NULL) {
	    return;
	}
	*++real_value = '\0';
	_putenv(shadow_env[i].real_assertion);
	free(shadow_env[i].shadow_name);
	free(shadow_env[i].shadow_value);
	free(shadow_env[i].real_assertion);

	memmove(&shadow_env[i],
		&shadow_env[i+1],
		sizeof(shadow_env_t) * (shadow_used - i));
	--shadow_used;
    }
    else if (getenv(name)) {
	char* assertion = malloc(strlen(name)+2);
	if (assertion == NULL) {
	    return;
	}
	sprintf(assertion, "%s=", name);
	_putenv(assertion);
	free(assertion);
    }
}

char* Downhill_Getenv(const char* name)
{
    shadow_env_t* shadow;
    
    shadow = getshadow(name);
    if (shadow) {
	return shadow->shadow_value;
    }
    else {
	return NULL;
    }
}

