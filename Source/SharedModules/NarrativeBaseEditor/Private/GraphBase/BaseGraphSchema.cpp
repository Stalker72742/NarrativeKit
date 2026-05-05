#include "GraphBase/BaseGraphSchema.h"

#include "GraphEditorSettings.h"

const FName PC_Exec(TEXT("exec"));
const FName PC_Boolean(TEXT("bool"));
const FName PC_Byte(TEXT("byte"));
const FName PC_Class(TEXT("class"));
const FName PC_Int(TEXT("int"));
const FName PC_Int64(TEXT("int64"));
const FName PC_Float(TEXT("float"));
const FName PC_Double(TEXT("double"));
const FName PC_Real(TEXT("real"));
const FName PC_Name(TEXT("name"));
const FName PC_Delegate(TEXT("delegate"));
const FName PC_MCDelegate(TEXT("mcdelegate"));
const FName PC_Object(TEXT("object"));
const FName PC_Interface(TEXT("interface"));
const FName PC_String(TEXT("string"));
const FName PC_Text(TEXT("text"));
const FName PC_Struct(TEXT("struct"));
const FName PC_Wildcard(TEXT("wildcard"));
const FName PC_FieldPath(TEXT("fieldpath"));
const FName PC_Enum(TEXT("enum"));
const FName PC_SoftObject(TEXT("softobject"));
const FName PC_SoftClass(TEXT("softclass"));
const FName PSC_Self(TEXT("self"));
const FName PSC_Index(TEXT("index"));
const FName PSC_Bitmask(TEXT("bitmask"));
const FName PN_Execute(TEXT("execute"));
const FName PN_Then(TEXT("then"));
const FName PN_Completed(TEXT("Completed"));
const FName PN_DelegateEntry(TEXT("delegate"));
const FName PN_EntryPoint(TEXT("EntryPoint"));
const FName PN_Self(TEXT("self"));
const FName PN_Else(TEXT("else"));
const FName PN_Loop(TEXT("loop"));
const FName PN_After(TEXT("after"));
const FName PN_ReturnValue(TEXT("ReturnValue"));
const FName PN_ObjectToCast(TEXT("Object"));
const FName PN_Condition(TEXT("Condition"));
const FName PN_Start(TEXT("Start"));
const FName PN_Stop(TEXT("Stop"));
const FName PN_Index(TEXT("Index"));
const FName PN_Item(TEXT("Item"));
const FName PN_CastSucceeded(TEXT("then"));
const FName PN_CastFailed(TEXT("CastFailed"));
const FString PN_CastedValuePrefix(TEXT("As"));

const UScriptStruct* VectorStruct = nullptr;
const UScriptStruct* Vector3fStruct = nullptr;
const UScriptStruct* RotatorStruct = nullptr;
const UScriptStruct* TransformStruct = nullptr;
const UScriptStruct* LinearColorStruct = nullptr;
const UScriptStruct* ColorStruct = nullptr;


UBaseGraphSchema::UBaseGraphSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	VectorStruct = TBaseStructure<FVector>::Get();
	Vector3fStruct = TVariantStructure<FVector3f>::Get();
	RotatorStruct = TBaseStructure<FRotator>::Get();
	TransformStruct = TBaseStructure<FTransform>::Get();
	LinearColorStruct = TBaseStructure<FLinearColor>::Get();
	ColorStruct = TBaseStructure<FColor>::Get();
}

const FPinConnectionResponse UBaseGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
    if (A->Direction == B->Direction)
        return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Same direction"));
    return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

FLinearColor UBaseGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
    const FName TypeName = PinType.PinCategory;
	const UGraphEditorSettings* Settings = GetDefault<UGraphEditorSettings>();

	if (TypeName == PC_Exec)
	{
		return Settings->ExecutionPinTypeColor;
	}
	else if (TypeName == PC_Object || TypeName == PC_FieldPath)
	{
		return Settings->ObjectPinTypeColor;
	}
	else if (TypeName == PC_Interface)
	{
		return Settings->InterfacePinTypeColor;
	}
	else if (TypeName == PC_Real)
	{
		return Settings->RealPinTypeColor;
	}
	else if (TypeName == PC_Boolean)
	{
		return Settings->BooleanPinTypeColor;
	}
	else if (TypeName == PC_Byte || TypeName == PC_Enum)
	{
		return Settings->BytePinTypeColor;
	}
	else if (TypeName == PC_Int)
	{
		return Settings->IntPinTypeColor;
	}
	else if (TypeName == PC_Int64)
	{
		return Settings->Int64PinTypeColor;
	}
	else if (TypeName == PC_Struct)
	{
		if ((PinType.PinSubCategoryObject == VectorStruct) || (PinType.PinSubCategoryObject == Vector3fStruct))
		{
			// vector
			return Settings->VectorPinTypeColor;
		}
		else if (PinType.PinSubCategoryObject == RotatorStruct)
		{
			// rotator
			return Settings->RotatorPinTypeColor;
		}
		else if (PinType.PinSubCategoryObject == TransformStruct)
		{
			// transform
			return Settings->TransformPinTypeColor;
		}
		else
		{
			return Settings->StructPinTypeColor;
		}
	}
	else if (TypeName == PC_String)
	{
		return Settings->StringPinTypeColor;
	}
	else if (TypeName == PC_Text)
	{
		return Settings->TextPinTypeColor;
	}
	else if (TypeName == PC_Wildcard)
	{
		if (PinType.PinSubCategory == PSC_Index)
		{
			return Settings->IndexPinTypeColor;
		}
		else
		{
			return Settings->WildcardPinTypeColor;
		}
	}
	else if (TypeName == PC_Name)
	{
		return Settings->NamePinTypeColor;
	}
	else if (TypeName == PC_SoftObject)
	{
		return Settings->SoftObjectPinTypeColor;
	}
	else if (TypeName == PC_SoftClass)
	{
		return Settings->SoftClassPinTypeColor;
	}
	else if (TypeName == PC_Delegate)
	{
		return Settings->DelegatePinTypeColor;
	}
	else if (TypeName == PC_Class)
	{
		return Settings->ClassPinTypeColor;
	}

	// Type does not have a defined color!
	return Settings->DefaultPinTypeColor;
}

FLinearColor UBaseGraphSchema::GetSecondaryPinTypeColor(const FEdGraphPinType& PinType) const
{
	if (PinType.IsMap())
	{
		FEdGraphPinType FakePrimary = PinType;
		FakePrimary.PinCategory = FakePrimary.PinValueType.TerminalCategory;
		FakePrimary.PinSubCategory = FakePrimary.PinValueType.TerminalSubCategory;
		FakePrimary.PinSubCategoryObject = FakePrimary.PinValueType.TerminalSubCategoryObject;

		return GetPinTypeColor(FakePrimary);
	}
	else
	{
		const UGraphEditorSettings* Settings = GetDefault<UGraphEditorSettings>();
		return Settings->WildcardPinTypeColor;
	}
}
