#include <emscripten.h>
#include <stdio.h>

// declare a reusable JS function
EM_JS(void, jsFunction, (int n), {
  console.log("Call from EM_JS" + n);
})

int main() {
  printf("WASM Ready\n");

  // call JS function
  emscripten_run_script("console.log('Hello from C!')");

  // call JS function
  emscripten_async_run_script("console.log('Hello from C - ASYNC!')", 2000);

  // Get return value from JS function - INT
  int jsVal = emscripten_run_script_int("getNum()");

  // Get return value from JS function - STR
  char * jsValStr = emscripten_run_script_string("getStr()");


  printf("Val from getNum(): %d\n", jsVal);
  printf("Val from getStr(): %s\n", jsValStr);

  // Execute EM_JS fn
  jsFunction(144);

  return 1;
}
