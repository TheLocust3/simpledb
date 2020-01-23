#ifndef QUERY_H
#define QUERY_H

typedef unsigned short operation;

#define QUERY_READ 0
#define QUERY_WRITE 1
#define QUERY_REMOVE 2

typedef unsigned short response_code;

#define RESPONSE_SUCCESS 0
#define RESPONSE_FAILURE 1

typedef struct query_request {
    operation op;
    long key;
    long val;
} query_request;

typedef struct query_response {
    operation op;
    response_code code;
    long val;
} query_response;

void query_print(query_request q);

#endif
