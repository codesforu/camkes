/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <camkes.h>
#include <stdio.h>
#include <stdlib.h>

int run() {
    const char *shello = "hello world";
    const char *smore = "a longer string that will overflow the message registers on ARM";
    char *s;
    int i = 42, j;
    int p, p1, p2;
    float f = 273421.4274, g;
    double d = 273421.4274, e;

    printf("Starting the client\n");
    printf("-------------------\n");

    j = _control_echo_int(i);
    printf("echo_int: %d -> %d\n",i, j);

    g = _control_echo_float(f);
    printf("echo_float: %f -> %f\n",f, g);

    e = _control_echo_double(d);
    printf("echo_double: %f -> %f\n",d, e);

    j = _control_echo_mix(d);
    printf("echo_mix: %f -> %d\n",d, j);

    s = _control_echo_string(shello);
    printf("echo_string: \"%s\" -> \"%s\"\n", shello, s);
    free(s);

    s = _control_echo_string(smore);
    printf("echo_string: \"%s\" -> \"%s\"\n", smore, s);
    free(s);

    p = 123;
    p2 = _control_echo_parameter(p, &p1);
    printf("echo_parameter: %d -> %d (returned = %d)\n", p, p1, p2);

    p = 100;
    _control_increment_parameter(&p);
    printf("increment_parameter: 100 -> %d\n", p);

    printf("After the client\n");
    return 0;
}
