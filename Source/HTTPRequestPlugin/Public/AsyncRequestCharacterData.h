// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "AsyncRequestCharacterData.generated.h"


USTRUCT(BlueprintType)
struct FCharacterData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FText Character_ID;
	
	UPROPERTY(BlueprintReadOnly)
	FText Character_Name;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Status;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Species;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Gender;

	UPROPERTY(BlueprintReadOnly)
	FText Character_Origin_Name;
	
	UPROPERTY(BlueprintReadOnly)
	FString Character_Image_URL;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadDataDelegate, FCharacterData, Data);

UCLASS()
class HTTPREQUESTPLUGIN_API UAsyncRequestCharacterData : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncRequestCharacterData* DownloadCharacerData();

	void Start(FString URL);

	UPROPERTY(BlueprintAssignable)
	FDownloadDataDelegate OnSuccess;

private:
	void HandleDataRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
