#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "BaseGraphSchema.generated.h"

/**
 * @brief Base schema with common connection rules.
 * @note Override GetGraphContextActions in subclass to add node types.
 */
UCLASS(Abstract)
class NARRATIVEBASEEDITOR_API UBaseGraphSchema : public UEdGraphSchema
{
    GENERATED_BODY()
public:
    
    UBaseGraphSchema(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
    virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
    virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;
    virtual FLinearColor GetSecondaryPinTypeColor(const FEdGraphPinType& PinType) const override;
};
