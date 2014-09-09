/*  AccountsClientC - A libary to access Mojang's UUID API.
  Copyright 2014 Daemon Lee Schmidt

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

/* Random TODOs:
  Implement JSON parsing with some type of external library, most likely jansson
  wrap low-level function into higher level stuff, getname, getuuid, etc. Using
  said json library.
*/

#include "AccountsClient.h"

void* accountsclient_Init() {
  CURL* curl_handle;

#ifdef _WIN32
  curl_global_init(CURL_GLOBAL_DEFAULT);
#else
  curl_global_init(CURL_GLOBAL_SSL);
#endif

  curl_handle = curl_easy_init();

  if (curl_handle) {
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 2L);
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 2L);

    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);

    /* TODO Verbose mode
    if (0) curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L); */

    return curl_handle;
  }
  return NULL;
}

/* This function was designed to be hacked, go crazy! */
size_t accountsclient_callback(char* ptr, size_t size, size_t nmemb,
                               void* userdata) {
  printf("%s\n", ptr);
  return nmemb;
}

void accountsclient_Get(void* minegetter, char* url) {
  CURLcode res;
  curl_easy_setopt(minegetter, CURLOPT_WRITEFUNCTION, accountsclient_callback);

  curl_easy_setopt(minegetter, CURLOPT_URL, url);

  res = curl_easy_perform(minegetter);

  if (res != CURLE_OK)
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
}

void accountsclient_UUID(void* minegetter, char* username) {
  /* data may look insane, but it's really just a simple hand-written JSON. */
  CURLcode res;
  struct curl_slist* header = NULL;
  char data[49] = "[{\"name\":\"";
  header = curl_slist_append(header, "Content-Type: application/json");
  strcat(data, username);
  strcat(data, "\",\"agent\":\"Minecraft\"}]");

  curl_easy_setopt(minegetter, CURLOPT_HTTPHEADER, header);

  curl_easy_setopt(minegetter, CURLOPT_WRITEFUNCTION, accountsclient_callback);

  curl_easy_setopt(minegetter, CURLOPT_URL,
                   "https://api.mojang.com/profiles/page/1");

  curl_easy_setopt(minegetter, CURLOPT_POSTFIELDS, data);

  res = curl_easy_perform(minegetter);

  if (res != CURLE_OK)
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
}

void accountsclient_Profile(void* minegetter, char* username, int timestamp) {
  /*
  Not technically safe for January 19, 2038! But screw it! Minecraft will be
  dead by then anyway... Or Minecraft 2: Modern Cobblefare will be around.
  */
  char url[79] = "https://api.mojang.com/users/profiles/minecraft/";
  char timestampstr[10];
  sprintf(timestampstr, "%d", timestamp);
  strcat(url, username);
  strcat(url, "?at=");
  strcat(url, timestampstr);

  accountsclient_Get(minegetter, url);
}

void accountsclient_NameHistroy(void* minegetter, char* UUID) {
  char url[76] = "https://api.mojang.com/user/profiles/";
  strcat(url, UUID);
  strcat(url, "/names");

  accountsclient_Get(minegetter, url);
}

void accountsclient_ProfileSkin(void* minegetter, char* UUID) {
  char url[91] = "https://sessionserver.mojang.com/session/minecraft/profile/";
  strcat(url, UUID);

  accountsclient_Get(minegetter, url);
}

void accountsclient_Clean(void* minegetter) {
  curl_easy_cleanup(minegetter);
  curl_global_cleanup();
}
