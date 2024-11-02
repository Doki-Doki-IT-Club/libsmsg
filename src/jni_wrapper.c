#include <stdio.h>
#include <stdlib.h>
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

static void smDestroy(JNIEnv *env, jobject obj, jlong ptr)
{
	(void) env;
	(void) obj;
	sm_destroy((void *) ptr);
}

static jint smGetSize(JNIEnv *env, jobject obj, jlong ptr)
{
	(void) env;
	(void) obj;
	return (jint) sm_get_size((void *) ptr);
}

static jint smGetType(JNIEnv *env, jobject obj, jlong ptr)
{
	(void) env;
	(void) obj;
	return (jint) sm_get_type((void *) ptr);
}

static jlong smSizeByType(JNIEnv *env, jobject obj, jlong ptr)
{
	(void) env;
	(void) obj;
	return (jint) sm_size_by_type((void *) ptr);
}

static JNINativeMethod funcs[] = {
	{ "smCreate", "(I)J", (void *) &smCreate },
	{ "smDestroy", "(J)V", (void *) &smDestroy },
    { "smGetSize", "(J)I", (void *) &smGetSize },
    { "smGetType", "(J)I", (void *) &smGetType },
    { "smSizeByType", "(J)J", (void *) &smSizeByType },
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