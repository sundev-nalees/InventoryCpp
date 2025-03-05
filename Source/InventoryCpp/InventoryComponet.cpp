// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponet.h"
#include "InventoryCppCharacter.h"

// Sets default values for this component's properties
UInventoryComponet::UInventoryComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame


bool UInventoryComponet::AddItem(FInventoryItemData NewItem)
{
	float ItemTotalWeight = NewItem.Weight * NewItem.Quantity;

	if(CurrentWeight+ItemTotalWeight>MaxWeight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add %s. Over the Max Weight Limit!!!!!"), *NewItem.ItemName.ToString());
		return false;
	}
	
	Items.Add(NewItem);
	CurrentWeight += ItemTotalWeight;

	UE_LOG(LogTemp, Warning, TEXT("%s Added to the Inventory . Current Weight : %f/%f"), *NewItem.ItemName.ToString(),CurrentWeight,MaxWeight);
	
	OnWeightChanged.Broadcast();
	return true;
}

bool UInventoryComponet::RemoveItem(FName ItemName, int32 Quantity)
{
	for(int32 i=0;i<Items.Num();i++)
	{
		if (Items[i].ItemName == ItemName)
		{
			if (Items[i].Quantity < Quantity)
			{
				UE_LOG(LogTemp, Warning, TEXT("Not enough %s to remove!"), *ItemName.ToString());
				return false;
			}

			float WeightToRemove = Items[i].Weight * Quantity;
			Items[i].Quantity -= Quantity;
			CurrentWeight -= WeightToRemove;

			if (Items[i].Quantity <= 0)
			{
				Items.RemoveAt(i);
			}

			UE_LOG(LogTemp, Warning, TEXT("%s Removed From the Inventory . Current Weight : %f/%f"), *ItemName.ToString(), CurrentWeight, MaxWeight);

			OnWeightChanged.Broadcast();

			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Item %s not Found!!!"), *ItemName.ToString());

	return false;
}

EWeightStage UInventoryComponet::GetWeightStage() const
{
	if(CurrentWeight<MaxWeight*0.5)
	{
		return EWeightStage::NORMAL;
	}
	else if(CurrentWeight<MaxWeight*0.8)
	{
		return EWeightStage::HEAVY;
	}
	else
	{
		return EWeightStage::OVERBURDENED;
	}
	
}

void UInventoryComponet::DisplayInventory() const
{
	UE_LOG(LogTemp, Log, TEXT("------------------Inventory-----------------"));

	for(const auto& Item:Items)
	{
		UE_LOG(LogTemp, Log, TEXT("- %s x%d (Weight: %f)"), *Item.ItemName.ToString(), Item.Quantity, Item.Weight * Item.Quantity);
	}
	UE_LOG(LogTemp, Log, TEXT("Total Weight: %f/%f"), CurrentWeight, MaxWeight);
	EWeightStage Stage = GetWeightStage();
	FString WeightStatus;
	switch (Stage) {
	case EWeightStage::NORMAL:
		WeightStatus = "Normal";
		break;
	case EWeightStage::HEAVY:
		WeightStatus = "Heavy - Movement slightly reduced";
		break;
	case EWeightStage::OVERBURDENED:
		WeightStatus = "Overburdened - Cannot move";
		break;
	}
	UE_LOG(LogTemp, Log, TEXT("Weight Status: %s"), *WeightStatus);
}

