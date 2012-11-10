/*-< CLITEST.C >-----------------------------------------------------*--------*
 * GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
 * (Post Relational Database Management System)                      *   /\|  *
 *                                                                   *  /  \  *
 *                          Created:     13-Jan-2000 K.A. Knizhnik   * / [] \ *
 *                          Last update: 13-Jan-2000 K.A. Knizhnik   * GARRET *
 *-------------------------------------------------------------------*--------*
 * Test for GigaBASE call level interface 
 * Spawn "subsql  clitest.sql" to start CLI server. 
 *-------------------------------------------------------------------*--------*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

typedef struct  person { 
    char        name[64];
    cli_int8_t  salary;
    char*       address;
    cli_real8_t weight;
    cli_int4_t  n_subordinates;
    cli_oid_t*  subordinates;
} person;

void* set_subordinates(int var_type, void* var_ptr, int len)
{
    person* p = (person*)var_ptr;
    if (p->subordinates != NULL) { 
	free(p->subordinates);
    }
    p->n_subordinates = len;
    p->subordinates = (cli_oid_t*)malloc(len*sizeof(cli_oid_t));
    return p->subordinates;
}

void* get_subordinates(int var_type, void* var_ptr, int* len)
{
    person* p = (person*)var_ptr;
    *len = p->n_subordinates;
    return p->subordinates;
}

int main()
{
    char* serverURL = "localhost:6100";
    int session, statement, statement2, rc, len;
    int i, n, salary;
    char name[256];
    cli_oid_t oid;
    person p;

    session = cli_open(serverURL, 10, 1);
    if (session < 0) { 
	fprintf(stderr, "cli_open failed with code %d\n", session);
	return EXIT_FAILURE;
    }

    statement = cli_statement(session, "insert into persons");
    if (statement < 0) { 
	fprintf(stderr, "cli_statement failed with code %d\n", statement);
	return EXIT_FAILURE;
    }

    if ((rc=cli_column(statement, "name", cli_asciiz, NULL, p.name)) != cli_ok
	|| (rc=cli_column(statement, "salary", cli_int4, NULL, &p.salary)) != cli_ok
	|| (rc=cli_column(statement, "address", cli_pasciiz, &len, &p.address)) != cli_ok
	|| (rc=cli_column(statement, "weight", cli_real8, NULL, &p.weight)) != cli_ok
	|| (rc=cli_array_column(statement, "subordinates", cli_array_of_oid, &p, 
				set_subordinates, get_subordinates)) != cli_ok)
    {
	fprintf(stderr, "cli_column 1 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    strcpy(p.name, "John Smith");
    p.salary = 75000;
    p.address = "1 Guildhall St., Cambridge CB2 3NH, UK";
    p.weight = 80.3;
    p.n_subordinates = 0;
    p.subordinates = NULL;
    rc = cli_insert(statement, &oid);
    if (rc != cli_ok) { 
	fprintf(stderr, "cli_insert failed with code %d\n", rc);
	return EXIT_FAILURE;
    }

    strcpy(p.name, "Joe Cooker");
    p.salary = 100000;
    p.address = "Outlook drive, 15/3";
    p.weight = 80.3;
    p.n_subordinates = 1;
    p.subordinates = &oid;
    rc = cli_insert(statement, NULL);
    if (rc != cli_ok) { 
	fprintf(stderr, "cli_insert 2 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    
    rc = cli_free(statement);
    if (rc != cli_ok) { 
	fprintf(stderr, "cli_free failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    
    p.subordinates = NULL;
    statement = cli_statement(session, 
			      "select * from persons where "
			      "length(subordinates) < %subordinates and salary > %salary");
    if (statement < 0) { 
	fprintf(stderr, "cli_statement 2 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    if ((rc=cli_column(statement, "name", cli_asciiz, NULL, p.name)) != cli_ok
	|| (rc=cli_column(statement, "salary", cli_int4, NULL, &p.salary)) != cli_ok
	|| (rc=cli_column(statement, "address", cli_pasciiz, &len, &p.address)) != cli_ok
	|| (rc=cli_column(statement, "weight", cli_real8, NULL, &p.weight)) != cli_ok
	|| (rc=cli_array_column(statement, "subordinates", cli_array_of_oid, &p, 
				set_subordinates, get_subordinates)) != cli_ok)
    {
	fprintf(stderr, "cli_column 2 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    if ((rc = cli_parameter(statement, "%subordinates", cli_int4, &n)) != cli_ok 
	|| (rc = cli_parameter(statement, "%salary", cli_int4, &salary)) != cli_ok)
    {
	fprintf(stderr, "cli_parameter failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    n = 2;
    salary = 90000;
    rc = cli_fetch(statement, cli_view_only);
    if (rc != 1) { 
	fprintf(stderr, "cli_fetch 1 returns %d instead of 1\n", rc);
	cli_commit(session);
	return EXIT_FAILURE;
    }
    n = 10;
    salary = 50000;
    rc = cli_fetch(statement, cli_for_update);
    if (rc != 2) { 
	fprintf(stderr, "cli_fetch 2 returns %d instead of 2\n", rc);
	return EXIT_FAILURE;
    }
    statement2 = cli_statement(session, "select * from persons where current = %oid");
    if (statement2 < 0) { 
	fprintf(stderr, "cli_statement 3 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
 
    if ((rc=cli_column(statement2, "name", cli_asciiz, NULL, name)) != cli_ok) { 
	fprintf(stderr, "cli_column 3 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    if ((rc = cli_parameter(statement2, "%oid", cli_oid, &oid)) != cli_ok) { 
	fprintf(stderr, "cli_parameter 3 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }	

    while ((rc = cli_get_next(statement)) == cli_ok) { 
	printf("%s\t%ld\t%lf\t%s\n", p.name, (long)p.salary, p.weight, p.address);
	if (p.n_subordinates > 0) { 
	    printf("Manages:\n");
	    for (i = 0; i < p.n_subordinates; i++) { 
		oid = p.subordinates[i];
		rc = cli_fetch(statement2, cli_view_only); 
		if (rc != 1) { 
		    fprintf(stderr, "cli_fetch by oid failed with code %d\n", rc);
		    return EXIT_FAILURE;
		}	
		if ((rc = cli_get_first(statement2)) != cli_ok) { 
		    fprintf(stderr, "cli_get_first failed with code %d\n", rc);
		    return EXIT_FAILURE;
		}
		printf("\t%s\n", name);
	    }
	}
	p.salary = p.salary*90/100;
	rc = cli_update(statement);
	if (rc != cli_ok) { 
	    fprintf(stderr, "cli_update failed with code %d\n", rc);
	    return EXIT_FAILURE;
	}
    }
    if (rc != cli_not_found) { 
	fprintf(stderr, "cli_get_next failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    if ((rc = cli_free(statement)) != cli_ok ||
	(rc = cli_free(statement2)) != cli_ok)
    {
	fprintf(stderr, "cli_free 2 failed with code %d\n", rc);
	return EXIT_FAILURE;	
    }
    if ((rc = cli_commit(session)) != cli_ok) { 
	fprintf(stderr, "cli_commit failed with code %d\n", rc);
	return EXIT_FAILURE;	
    }
    statement = cli_statement(session, "select * from persons order by salary");
    if (statement < 0) { 
	fprintf(stderr, "cli_statement 4 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }	
    if ((rc=cli_column(statement, "salary", cli_int4, NULL, &salary)) != cli_ok) { 
	fprintf(stderr, "cli_column 4 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    rc = cli_fetch(statement, cli_for_update);
    if (rc != 2) { 
	fprintf(stderr, "cli_fetch 4 failed with code %d\n", rc);
	return EXIT_FAILURE;
    }	
    printf("New salaries:\n");
    while ((rc = cli_get_prev(statement)) == cli_ok) { 
	printf("\t%d\n", salary);
    }
    if (rc != cli_not_found) { 
	fprintf(stderr, "cli_get_prev failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    if ((rc = cli_remove(statement)) != cli_ok) { 
	fprintf(stderr, "cli_remove failed with code %d\n", rc);
	return EXIT_FAILURE;
    }
    if ((rc = cli_free(statement)) != cli_ok) { 
	fprintf(stderr, "cli_free 3 failed with code %d\n", rc);
	return EXIT_FAILURE;	
    }
    if ((rc = cli_close(session)) != cli_ok) { 
	fprintf(stderr, "cli_close failed with code %d\n", rc);
	return EXIT_FAILURE;	
    }
    printf("*** CLI test sucessfully passed!\n");
    return EXIT_SUCCESS;
}
	

