#pragma once
class NiUpdateData {
public:
	NiUpdateData(float afTime = 0, bool abUpdateControllers = 0, bool abIsMultiThreaded = 0, bool abyte6 = 0, bool abUpdateGeomorphs = 0, bool abUpdateShadowSceneNode = 0)
		: fTime(afTime), bUpdateControllers(abUpdateControllers), bIsMultiThreaded(abIsMultiThreaded), byte6(abyte6), bUpdateGeomorphs(abUpdateGeomorphs), bUpdateShadowSceneNode(abUpdateShadowSceneNode)
	{}
	~NiUpdateData() {};

	float fTime;
	bool bUpdateControllers;
	bool bIsMultiThreaded;
	bool byte6;
	bool bUpdateGeomorphs;
	bool bUpdateShadowSceneNode;
};