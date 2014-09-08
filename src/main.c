/*  mineget - A CLI program to access Mojang's UUID API.
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

/* Project Headers */
#include "AccountsClient.h"

/* This is all pretty terrible and useless,
but it's only used for testing while I get thelibrary figured out.
Stay tuned for when this isn't completely garbage. */

int main(int argc, const char* argv[]) {
  void* minegetter = accountclient_Init();

  int i;
  if (minegetter) {
    if (argc > 1) {
      for (i = 1; i < argc; i++) {
        char UUID[33];
        strcpy(UUID, argv[i]);
        accountclient_NameHistroy(minegetter, UUID);
      }
    } else {
      printf("wtf beef\n");
    }

    if (argc > 1) {
      for (i = 1; i < argc; i++) {
        char username[17];
        strcpy(username, argv[i]);
        /* TODO User timestamps */
        accountclient_Profile(minegetter, username, (int)time(NULL));
      }
    } else {
      printf("wtf beef\n"); /* TODO Proper CLI UI stuff */
    }
  }

  if (minegetter) {
    if (argc > 1) {
      for (i = 1; i < argc; i++) {
        char UUID[33];
        strcpy(UUID, argv[i]);
        accountclient_ProfileSkin(minegetter, UUID);
      }
    } else {
      printf("wtf beef\n");
    }
  }

  accountclient_Clean(minegetter);

  return 0;
}
