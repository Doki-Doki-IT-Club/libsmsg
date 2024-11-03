#include <jni.h>
#include <string.h>
#include <stdlib.h>

#include "../smsg.h"

// +-----------------------------+
// |  S U P E R   M E S S A G E  |
// +-----------------------------+

static const char * JNIT_CLASS = "SuperMessage";

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
	const char * str;
	(void) obj;
	str = (*env)->GetStringUTFChars(env, value, 0);
	sm_set_value((void *) msg, (int) field_num, (void *) str);
}

static jint smParseFieldNum(JNIEnv *env, jobject obj, jlong msg, jstring field_name)
{
	const char * field;
	(void) obj;
	field = (*env)->GetStringUTFChars(env, field_name, 0);
	return (jint) sm_parse_field_num((void *) msg, field);
}

static jint smParseTypeNum(JNIEnv *env, jobject obj, jstring type_name)
{
	const char * type;
	(void) obj;
	type = (*env)->GetStringUTFChars(env, type_name, 0);
	return (jint) sm_parse_type_num(type);
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

static jstring smStringPT(JNIEnv *env, jobject obj, jlong value)
{
	char sval[1024];
	(void)obj;
	snprintf(sval, sizeof(sval), "%s", (char *) value);
	return (*env)->NewStringUTF(env, sval);
}

static JNINativeMethod sm_funcs[] = {
	{ "smCreate", "(I)J", (void *) &smCreate },
	{ "smDestroy", "(J)V", (void *) &smDestroy },
    { "smGetSize", "(J)I", (void *) &smGetSize },
    { "smGetType", "(J)I", (void *) &smGetType },
	{ "smGetValue", "(JI)J", (void *) &smGetValue },
    { "smSizeByType", "(J)J", (void *) &smSizeByType },
	{ "smSetIntValue", "(JIJ)V", (void *) &smSetIntValue },
	{ "smSetStringValue", "(JILjava/lang/String;)V", (void *) &smSetStringValue },
	{ "smParseFieldNum", "(JLjava/lang/String;)I", (void *) &smParseFieldNum },
	{ "smParseTypeNum", "(Ljava/lang/String;)I", (void *) &smParseTypeNum },
	{ "smIntTP", "(I)J", (void *) &smIntTP },
	{ "smIntPT", "(J)I", (void *) &smIntPT },
	{ "smStringPT", "(J)Ljava/lang/String;", (void *) &smStringPT },
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv *env;
	jclass cls;
	jint res;

	(void)reserved;

	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_8) != JNI_OK) { return -1; }

	cls = (*env)->FindClass(env, JNIT_CLASS);
	if (cls == NULL) { return -1; }

	res = (*env)->RegisterNatives(env, cls, sm_funcs, sizeof(sm_funcs)/sizeof(*sm_funcs));
	if (res != 0) { return -1; }

	return JNI_VERSION_1_8;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved)
{
	JNIEnv *env;
	jclass  cls;

	(void)reserved;

	if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_8) != JNI_OK) { return; }

	cls = (*env)->FindClass(env, JNIT_CLASS);
	if (cls == NULL) { return; }

	(*env)->UnregisterNatives(env, cls);
}