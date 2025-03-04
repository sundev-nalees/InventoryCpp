// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponet.generated.h"

UENUM(BlueprintType)
enum class EWeightStage:uint8
{
	NORMAL,
	HEAVY,
	OVERBURDENED
};

USTRUCT(BlueprintType)

struct FInventoryItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	FInventoryItemData():ItemName("Unknown"),Weight(0.0f),Quantity(1){}

	FInventoryItemData(FName Name,float ItemWeight,int32 ItemQuantity):ItemName(Name),Weight(ItemWeight),Quantity(ItemQuantity){}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYCPP_API UInventoryComponet : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float MaxWeight;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	float CurrentWeight;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FInventoryItemData>Items;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FInventoryItemData NewItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(FName ItemName, int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	EWeightStage GetWeightStage() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DisplayInventory() const;


		
};
