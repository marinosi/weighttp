/*
 * weighttp - a lightweight and simple webserver benchmarking tool
 *
 * Author:
 *     Copyright (c) 2009-2011 Thomas Porzelt
 *
 * License:
 *     MIT, see COPYING file
 */

#ifndef WEIGHTTP_H
#define WEIGHTTP_H 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <netdb.h>

#include <ev.h>
#include <pthread.h>

#define CLIENT_BUFFER_SIZE 32 * 1024

#define W_MALLOC(t, n) ((t*) calloc((n), sizeof(t)))
#define W_REALLOC(p, t, n) ((t*) realloc(p, (n) * sizeof(t)))
#define W_ERROR(f, ...) fprintf(stderr, "error: " f "\n", __VA_ARGS__)
#define UNUSED(x) ( (void)(x) )

/* DPRINTF */
#ifdef DEBUG
#define DPRINTF(format, ...)				\
	fprintf(stderr, "%s [%d] " format "\n", 	\
	__FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define DPRINTF(...)
#endif

#define MMIN(a, b) ((a) < (b) ? (a) : (b))

struct Config;
typedef struct Config Config;
struct Stats;
typedef struct Stats Stats;
struct Worker;
typedef struct Worker Worker;
struct Client;
typedef struct Client Client;
struct Request;
typedef struct Request Request;

#include "client.h"
#include "worker.h"


struct Config {
	uint64_t req_count;
	uint8_t thread_count;
	uint16_t concur_count;
	uint8_t keep_alive;

	struct Request *requests;
};

#define MAX_REQUEST_LEN 512
struct Request {
	uint32_t request_size;
	struct addrinfo *saddr;
	char *request;
	Request *next;
};

uint64_t str_to_uint64(char *str);

#endif
