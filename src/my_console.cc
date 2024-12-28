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

using v8::Context;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
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
  SetMethod(context, target, "log", Log);
}

void RegisterExternalReferences(ExternalReferenceRegistry* registry) {
  registry->Register(Log);
}

}  // namespace os
}  // namespace node

NODE_BINDING_CONTEXT_AWARE_INTERNAL(my_console, node::my_console::Initialize)
NODE_BINDING_EXTERNAL_REFERENCE(my_console, node::my_console::RegisterExternalReferences)
