char *ua_list[]={"Mozilla/5.0","Chrome/120.0","Safari/537.36"};
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

struct response { long code; size_t size; char body[4096]; };

size_t write_cb(void *ptr, size_t size, size_t nmemb, void *ud){
    struct response *r = (struct response*)ud;
    size_t n = size*nmemb;
    if(r->size + n < sizeof(r->body)){
        memcpy(r->body + r->size, ptr, n);
    }
    r->size += n;
    return n;
}

struct response send_request(const char *url, const char *cookie, const char *header){
    CURL *c = curl_easy_init();
    struct response r; memset(&r,0,sizeof(r));
    struct curl_slist *h=NULL;

    if(!c) return r;

    curl_easy_setopt(c, CURLOPT_URL, url);
    curl_easy_setopt(c, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(c, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(c, CURLOPT_WRITEDATA, &r);

    if(cookie && *cookie) curl_easy_setopt(c, CURLOPT_COOKIE, cookie);
    if(header && *header){ h=curl_slist_append(h, header); curl_easy_setopt(c, CURLOPT_HTTPHEADER, h); }

    int retries = 2;
    while(retries--){
        CURLcode res = curl_easy_perform(c);
        curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &r.code);

        if(r.code == 429){ sleep(2); continue; } // rate limit
        break;
    }

    curl_easy_cleanup(c);
    if(h) curl_slist_free_all(h);
    return r;
}
