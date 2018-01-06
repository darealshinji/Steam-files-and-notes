#include <stdio.h>
#include "curl-enums.h"

#if defined(WIN32) || defined(_WIN32)
# define CURL_EXTERN __declspec(dllexport)
#else
# define CURL_EXTERN
#endif

typedef void CURL;

struct curl_slist {
  char *data;
  struct curl_slist *next;
};

CURL_EXTERN CURL *curl_easy_init() {
  return NULL;
}

CURL_EXTERN CURLcode curl_easy_setopt(CURL *handle, CURLoption option, ...) {
  return 0;
}

CURL_EXTERN CURLcode curl_easy_perform(CURL *handle) {
  return 0;
}

CURL_EXTERN void curl_easy_cleanup(CURL *handle) {
  return;
}

CURL_EXTERN struct curl_slist *curl_slist_append(struct curl_slist *list, const char *string) {
  return NULL;
}

CURL_EXTERN void curl_slist_free_all(struct curl_slist *list) {
  return;
}

