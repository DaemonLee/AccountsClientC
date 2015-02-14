/*  AccountsClientC - A libary to access Mojang's UUID API.
  Copyright 2015 Daemon Lee Schmidt

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

#ifndef ACCOUNTSCLIENT_H
#define ACCOUNTSCLIENT_H

/* System Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Curl Headers */
#include <curl/curl.h>

void* accountsclient_Init();

void accountsclient_Get(void* minegetter, char* url);

void accountsclient_UUID(void* minegetter, char* username);

size_t accountsclient_callback(char* ptr, size_t size, size_t nmemb,
                               void* userdata);

void accountsclient_Profile(void* minegetter, char* username, int timestamp);

void accountsclient_NameHistroy(void* minegetter, char* UUID);

void accountsclient_ProfileSkin(void* minegetter, char* UUID);

void accountsclient_Clean(void* minegetter);

#endif /* ACCOUNTSCLIENT_H */
