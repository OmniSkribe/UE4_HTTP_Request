// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncRequestCharacterData.h"

UAsyncRequestCharacterData* UAsyncRequestCharacterData::DownloadCharacerData()
{
	UAsyncRequestCharacterData* DownloadTask = NewObject<UAsyncRequestCharacterData>();
	
	FString charID = FString::FromInt(FMath::RandRange(1, 671));
	FString URL = TEXT("https://rickandmortyapi.com/api/character/" + charID);
	
	DownloadTask->Start(URL);

	return DownloadTask;
}

void UAsyncRequestCharacterData::Start(FString URL)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAsyncRequestCharacterData::HandleDataRequest);
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->ProcessRequest();
}

void UAsyncRequestCharacterData::HandleDataRequest(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (bSucceeded && HttpResponse.IsValid() && HttpResponse->GetContentLength() > 0)
	{
		FCharacterData local_data;

		UE_LOG(LogTemp, Warning, TEXT("REQUEST RECIEVED"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HttpResponse->GetContentAsString());

		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
		TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());

		if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
		{
			local_data.Character_ID = FText::FromString(FString::FromInt(JsonObject->GetIntegerField("id")));
			local_data.Character_Name = FText::FromString( JsonObject->GetStringField("name") );
			local_data.Character_Status = FText::FromString(JsonObject->GetStringField("status"));
			local_data.Character_Species = FText::FromString(JsonObject->GetStringField("species"));
			local_data.Character_Gender = FText::FromString(JsonObject->GetStringField("gender"));
			local_data.Character_Origin_Name = FText::FromString(JsonObject->GetObjectField("origin")->GetStringField("name"));
			local_data.Character_Image_URL = JsonObject->GetStringField("image");

			OnSuccess.Broadcast(local_data);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Something wrong"));
			//OnFail.Broadcast(nullptr);
		}
	}
}