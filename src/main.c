/*  mineget - A CLI program to access Mojang's UUID API.
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

/* Project Headers */
#include "AccountsClient.h"

/* This is all pretty terrible and useless,
but it's only used for testing while I get the library figured out.
Stay tuned for when this isn't completely garbage. */

/* TODO Proper CLI UI stuff */
/* TODO User timestamps */

int main(int argc, const char* argv[]) {
  void* minegetter = accountsclient_Init();

  int i;
  char username[17];
  char UUID[33];
  if (minegetter) {
    for (i = 1; i < argc; ++i) {
      if (strlen(argv[i]) <= 16) {
        strcpy(username, argv[i]);
        accountsclient_Profile(minegetter, username, (int)time(NULL));
        accountsclient_UUID(minegetter, username);
      } else if (strlen(argv[i]) == 32) {
        strcpy(UUID, argv[i]);
        accountsclient_NameHistroy(minegetter, UUID);
        accountsclient_ProfileSkin(minegetter, UUID);
      } else {
        fprintf(stderr, "Invalid username or UUID!\n");
      }
    }
  }
  accountsclient_Clean(minegetter);

  return 0;
}
