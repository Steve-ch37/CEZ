#include "../include/ezc.h"

/* Sentence stacks. */

void ezc_init_stc_stack(ezc_stc_stack *this)
{
    memset(this -> stack, sizeof(ezc_stc) << 6, 0);   // <<6 equals *64
    this -> top = -1;
}

ezc_stc ezc_get_top_stc_stack(ezc_stc_stack *this)
{
    if (this -> top == -1)
        return this -> stack[0];       // an empty item
    else
        return this -> stack[this -> top];
}

ezc_stc ezc_pop_stc_stack(ezc_stc_stack *this)
{
    if (top > 64 || top <= -1)
        return 1;
    --top;
    return this -> stack[top + 1];
}

int ezc_cmp_stc_level(ezc_stc item1, ezc_stc item2)
{
    return (item1 -> level) - (item2 -> level);
}


/* Variable stacks. */

void ezc_init_var_stack(ezc_var_stack *this)
{
    memset(this -> stack, sizeof(ezc_var) << 6, 0);   // <<6 equals *64
    this -> top = -1;
}

ezc_var ezc_get_top_var_stack(ezc_var_stack *this)
{
    if (this -> top == -1)
        return this -> stack[0];       // an empty item
    else
        return this -> stack[this -> top];
}

int ezc_push_var_stack(ezc_var_stack *this, ezc_var item)
{
    if (top >= 64 || top < -1)
        return 1;   // out of range
    this -> stack[++ this -> top] = item;
    return 0;
}

ezc_var ezc_pop_var_stack(ezc_var_stack *this)
{
    if (top > 64 || top <= -1)
        return 1;
    --top;
    return this -> stack[top + 1];
}

int ezc_cmp_var_level(ezc_var item1, ezc_var item2)
{
    return (item1 -> level) - (item2 -> level);
}

bool ezc_is_varname(ezc_var_stack *this, const char *name)
{
    for (count i = 0; i <= this -> top; i++)
        if (strcmp(this -> stack[i].name, name) == 0)
            return true;
    return false;
}

ezc_var_type ezc_get_var_type(ezc_var_stack *this, const char *name)
{
    for (count i = 0; i <= this -> top; i++)
        if (strcmp(this -> stack[i].name, name) == 0)
            return this -> stack[i].type;
    return -1;
}

/* Other runtime functions. */
void ezc_throw(int type, const char *msg)
{
    #include "../include/ezu.h"
    
    switch (type)
    {
        case ezc_error:
            ezu_set_err_colour(ezu_red, ezu_foreground);
            break;
        case ezu_warning:
            ezu_set_err_colour(ezu_yellow, ezu_foreground);
            break;
    }
    fputs(msg, stderr);
    ezu_init_colour();
}

const char *ezc_get_next(const char *src)
{
    // Get the end of the token.
    size_t idx = ezc_get_end(src);
    const char *now = src + idx + 1;
    // Point to the first character after this token.
    while (*now == ' ' || *now++ == '\t');
    
    return now;
}
