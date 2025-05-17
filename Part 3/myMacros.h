#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <stdio.h>

#define CHECK_RETURN_0(ptr) {if ((ptr) == NULL) return 0;}
#define CHECK_MSG_RETURN_0(ptr, msg) {if ((ptr) == NULL) { puts(msg); return 0; }}
#define FREE_CLOSE_FILE_RETURN_0(ptr, fp) {if(!ptr) CLOSE_RETURN_0(fp)}
#define CLOSE_RETURN_0(fp) {fclose(fp); return 0;}
