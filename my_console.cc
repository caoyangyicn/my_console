#include "env-inl.h"
#include "node_external_reference.h"
#include "string_bytes.h"

#ifdef __MINGW32__
# include <io.h>
#endif  // __MINGW32__

#ifdef __POSIX__
# include <climits>         // PATH_MAX on Solaris.
#endif  // __POSIX__

#include <array>
#include <cerrno>
#include <cstring>

namespace node {
namespace my_console {

using v8::Array;
using v8::ArrayBuffer;
using v8::Boolean;
using v8::Context;
using v8::Float64Array;
using v8::FunctionCallbackInfo;
using v8::Int32;
using v8::Integer;
using v8::Isolate;
using v8::Local;
using v8::MaybeLocal;
using v8::NewStringType;
using v8::Null;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;


static void Log(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  v8::String::Utf8Value str(isolate, args[0]);
  printf("%s\n", *str);
}



void Initialize(Local<Object> target,
                Local<Value> unused,
                Local<Context> context,
                void* priv) {
  Environment* env = Environment::GetCurrent(context);
  SetMethod(context, target, "log", Log);
  target
      ->Set(context,
            FIXED_ONE_BYTE_STRING(env->isolate(), "isBigEndian"),
            Boolean::New(env->isolate(), IsBigEndian()))
      .Check();
}

void RegisterExternalReferences(ExternalReferenceRegistry* registry) {
  registry->Register(Log);
}

}  // namespace os
}  // namespace node

NODE_BINDING_CONTEXT_AWARE_INTERNAL(my_console, node::my_console::Initialize)
NODE_BINDING_EXTERNAL_REFERENCE(my_console, node::my_console::RegisterExternalReferences)
