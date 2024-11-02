#include <jni.h>

#include "../smsg.h"

static const char *JNIT_CLASS = "SuperMessage";

static jlong smCreate(JNIEnv *env, jobject obj, jint type)
{
	void * msg;

	(void) env;
	(void) obj;

	msg = sm_create((int) type);
	return (jlong) msg;
}

static void smDestroy(JNIEnv *env, jobject obj, jlong msg)
{
	(void) env;
	(void) obj;
	sm_destroy((void *) msg);
}

static jint smGetSize(JNIEnv *env, jobject obj, jlong msg)
{
	(void) env;
	(void) obj;
	return (jint) sm_get_size((void *) msg);
}

static jint smGetType(JNIEnv *env, jobject obj, jlong msg)
{
	(void) env;
	(void) obj;
	return (jint) sm_get_type((void *) msg);
}

static jlong smSizeByType(JNIEnv *env, jobject obj, jlong msg)
{
	(void) env;
	(void) obj;
	return (jlong) sm_size_by_type((void *) msg);
}

static jlong smGetValue(JNIEnv *env, jobject obj, jlong msg, jint field_num)
{
	(void) env;
	(void) obj;
	return (jlong) sm_get_value((void *) msg, (int) field_num);
}

static void smSetIntValue(JNIEnv *env, jobject obj, jlong msg, jint field_num, jlong value)
{
	(void) env;
	(void) obj;
	sm_set_value((void *) msg, (int) field_num, (void *) value);
}

static void smSetStringValue(JNIEnv *env, jobject obj, jlong msg, jint field_num, jstring value)
{
	(void) env;
	(void) obj;
}

static jint smParseFieldNum(JNIEnv *env, jobject obj, jlong msg, jlong field_name)
{
	(void) env;
	(void) obj;
	return (jint) sm_parse_field_num((void *) msg, (void *) field_name);
}

static jlong smIntTP(JNIEnv *env, jobject obj, jint value)
{
	(void) env;
	(void) obj;
	return (jlong) intTP((int) value);
}

static jint smIntPT(JNIEnv *env, jobject obj, jlong value)
{
	(void) env;
	(void) obj;
	return (jint) intPT((void *) value);
}

static JNINativeMethod funcs[] = {
	{ "smCreate", "(I)J", (void *) &smCreate },
	{ "smDestroy", "(J)V", (void *) &smDestroy },
    { "smGetSize", "(J)I", (void *) &smGetSize },
    { "smGetType", "(J)I", (void *) &smGetType },
	{ "smGetValue", "(JI)J", (void *) &smGetValue },
    { "smSizeByType", "(J)J", (void *) &smSizeByType },
	{ "smSetIntValue", "(JIJ)V", (void *) &smSetIntValue },
	{ "smSetStringValue", "(JILjava/lang/String;)V", (void *) &smSetStringValue },
	{ "smParseFieldNum", "(JJ)I", (void *) &smParseFieldNum },
	{ "smIntTP", "(I)J", (void *) &smIntTP },
	{ "smIntPT", "(J)I", (void *) &smIntPT },
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv *env;
	jclass  cls;
	jint    res;

	(void)reserved;

	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_8) != JNI_OK)
		return -1;

	cls = (*env)->FindClass(env, JNIT_CLASS);
	if (cls == NULL)
		return -1;

	res = (*env)->RegisterNatives(env, cls, funcs, sizeof(funcs)/sizeof(*funcs));
	if (res != 0)
		return -1;

	return JNI_VERSION_1_8;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved)
{
	JNIEnv *env;
	jclass  cls;

	(void)reserved;

	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_8) != JNI_OK)
		return;

	cls = (*env)->FindClass(env, JNIT_CLASS);
	if (cls == NULL)
		return;

	(*env)->UnregisterNatives(env, cls);
}