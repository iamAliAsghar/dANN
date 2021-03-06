#include "NeuronJni.h"
#include "JniHelpers.h"
#include <jni.h>


JNIEXPORT jint JNICALL Java_syncleus_dann_Neuron_nativeConstructor(JNIEnv *Application, jobject SrcObject, jobject OwningLayerToSet, jobject DNAToSet, jdouble InitialBiasWeight)
{
	//if the class already has been constructed then just return the already established native id.
	Neuron *NativeThis = GetNativeNeuron(Application, SrcObject);
	if( NativeThis != 0 )
		return (jint) NativeThis;
	
	//this is truely a new class, generate a global reference
	NativeThis = new Neuron(GetNativeLayer(Application, OwningLayerToSet), GetNativeDNA(Application, DNAToSet), InitialBiasWeight);
	return (jint) NativeThis;
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_nativeDestructor(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	delete NativeThis;
}

JNIEXPORT jdouble JNICALL Java_syncleus_dann_Neuron_GetOutput(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->GetOutput();
}

JNIEXPORT jobject JNICALL Java_syncleus_dann_Neuron_GetDNA(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	DNA* NewJavaObject = NativeThis->GetDNA();

	jclass NewJavaClass = Application->FindClass("syncleus/dann/DNA");
	jmethodID NewJavaConstructor = Application->GetMethodID(NewJavaClass, "<init>", "(I)V");
	return Application->NewObject(NewJavaClass, NewJavaConstructor, (jint)NewJavaObject);
}

JNIEXPORT jdouble JNICALL Java_syncleus_dann_Neuron_GetDeltaTrain(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->GetDeltaTrain();
}

JNIEXPORT jobject JNICALL Java_syncleus_dann_Neuron_GetParentLayer(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	Layer* NewJavaObject = NativeThis->GetParentLayer();

	jclass NewJavaClass = Application->FindClass("syncleus/dann/Layer");
	jmethodID NewJavaConstructor = Application->GetMethodID(NewJavaClass, "<init>", "(I)V");
	return Application->NewObject(NewJavaClass, NewJavaConstructor, (jint)NewJavaObject);
}

JNIEXPORT jboolean JNICALL Java_syncleus_dann_Neuron_ConnectToNeuron(JNIEnv *Application, jobject SrcObject, jobject NeuronToConnectTo, jdouble InitialWeight)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->ConnectToNeuron(GetNativeNeuron(Application, NeuronToConnectTo), InitialWeight);
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_DisconnectAllDestinationSynapses(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->DisconnectAllDestinationSynapses();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_DisconnectAllSourceSynapses(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->DisconnectAllSourceSynapses();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_DisconnectAllSynapses(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->DisconnectAllSynapses();
}

JNIEXPORT jboolean JNICALL Java_syncleus_dann_Neuron_DisconnectSourceSynapse(JNIEnv *Application, jobject SrcObject, jobject SourceSynapseToDisconnect)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->DisconnectSourceSynapse(GetNativeSynapse(Application, SourceSynapseToDisconnect));
}

JNIEXPORT jboolean JNICALL Java_syncleus_dann_Neuron_DisconnectDestinationSynapse(JNIEnv *Application, jobject SrcObject, jobject DestinationSynapseToDisconnect)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->DisconnectSourceSynapse(GetNativeSynapse(Application, DestinationSynapseToDisconnect));
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Neuron_GetOutgoingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->GetOutgoingConnectionCount();
}

JNIEXPORT jint JNICALL Java_syncleus_dann_Neuron_GetIncommingConnectionCount(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->GetIncommingConnectionCount();
}

JNIEXPORT jdouble JNICALL Java_syncleus_dann_Neuron_Propogate(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	return NativeThis->Propogate();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_SetNeuronInput(JNIEnv *Application, jobject SrcObject, jdouble InputToSet)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->SetNeuronInput(InputToSet);
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_ResetNeuronInput(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->ResetNeuronInput();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_BackPropogateWeight(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->BackPropogateWeight();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_BackPropogateStructure(JNIEnv *Application, jobject SrcObject)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->BackPropogateStructure();
}

JNIEXPORT void JNICALL Java_syncleus_dann_Neuron_SetTrainingData(JNIEnv *Application, jobject SrcObject, jdouble TrainingToSet)
{
	//obtain the native this for the src object
	Neuron* NativeThis = GetNativeNeuron(Application, SrcObject);
	if(NativeThis == 0)
		throw 0;

	NativeThis->SetTrainingData(TrainingToSet);
}

