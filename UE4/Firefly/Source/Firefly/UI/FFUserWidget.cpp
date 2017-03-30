// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "FFUserWidget.h"

int32 UFFUserWidget::GetIntProperty(const FString& PropName) const
{
	for (TFieldIterator<UIntProperty> Prop(GetClass()); Prop; ++Prop)
	{
		if (Prop->GetName() == PropName)
			return Prop->GetPropertyValue(this);
	}

	return 0;
}

void UFFUserWidget::SetIntProperty(const FString& PropName, int32 val)
{
	for (TFieldIterator<UIntProperty> Prop(GetClass()); Prop; ++Prop)
	{
		if (Prop->GetName() == PropName)
			Prop->SetPropertyValue(this, val);
	}
}

FString UFFUserWidget::GetStringProperty(const FString& PropName) const
{
	static FString NullString("");

	for (TFieldIterator<UStrProperty> Prop(GetClass()); Prop; ++Prop)
	{
		if (Prop->GetName() == PropName)
			return Prop->GetPropertyValue(this);
	}

	return NullString;
}

void UFFUserWidget::SetStringProperty(const FString& PropName, const FString& val)
{
	for (TFieldIterator<UStrProperty> Prop(GetClass()); Prop; ++Prop)
	{
		if (Prop->GetName() == PropName)
			Prop->SetPropertyValue(this, val);
	}
}



