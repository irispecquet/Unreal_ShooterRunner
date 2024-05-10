// Copyright 2018 Francesco Desogus. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tweens/BaseTween.h"
#include "TweenManagerComponent.h"
#include "Engine/HitResult.h"
#include "TweenVector.generated.h"

class UTweenVectorLatentFactory;


/**
 * The UTweenVector handles the update of all Tweens that use only FVector.
 */
UCLASS(BlueprintType)
class TWEENMAKER_API UTweenVector : public UBaseTween
{
    GENERATED_BODY()

public:

    /**
     * @brief Constructor.
     */
    UTweenVector(const FObjectInitializer& ObjectInitializer);

    /*
     **************************************************************************
     * "Tween Info" methods
     **************************************************************************
     */

    /**
      * Returns the current value of the Tween.
      *
      * @return The current value.
      */
    UFUNCTION(BlueprintPure, meta = (KeyWords="Tween Current Value Info"), Category = "Tween|Info|Vector")
    FVector GetCurrentValue() const
    {
        return mCurrentValue;
    }

    /*
     **************************************************************************
     * Methods used internally. Should not be called.
     **************************************************************************
     */

    /**
     * @brief Init method for a generic TweenVector (internal usage only).
     * 
     * @param pFrom Initial value for the Tween.
     * @param pTo Ending value for the Tween.
     * @param pTweenType The Tween type.
     * @param pTweenSpace The space where the update takes place (i.e. world or local).
     * @param pDeleteTweenOnHit If true, the Tween is deleted when an object hits something.
     * @param pDeleteTweenOnOverlap If true, the Tween is deleted when an object overlaps something.
     * @param pTweenLatentProxy Proxy for latent Tweens. It's only valid if it's a Latent tween, otherwise it's null.
     */
    void Init(const FVector &pFrom,
              const FVector& pTo,
              ETweenVectorType pTweenType,
              ETweenSpace pTweenSpace,
              bool pDeleteTweenOnHit,
              bool pDeleteTweenOnOverlap,
              UTweenVectorLatentFactory* pTweenLatentProxy);

    /**
     * @brief Retrieves the Tween type.
     *
     * @return The Tween type.
     */
    ETweenVectorType GetTweenType() const
    {
        return mTweenType;
    }

    /*
     **************************************************************************
     * Blueprint delegates
     **************************************************************************
     */

    /// @brief Delegate called when the Tween starts (if it loops then it's called at each loop begin). Use only in Blueprints.
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Tween Start"))
    FBP_OnTweenVectorChange OnTweenStart;

    /// @brief Delegate called at each Tween's update. Use only in Blueprints.
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Tween Update"))
    FBP_OnTweenVectorChange OnTweenUpdate;

    /// @brief Delegate called when the Tween ends (if it loops then it's called at each loop end). Use only in Blueprints.
    UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Tween End"))
    FBP_OnTweenVectorChange OnTweenEnd;


    /**
     * @brief Delegate called when the Actor tween target is hit by something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from AActor and if the Tween type is either "Move" or "Scale".
     * Use only in Blueprints.
     */
    UPROPERTY(BlueprintAssignable)
    FBP_OnTweenActorHitVector OnTweenActorHit;

    /**
     * @brief Delegate called when the Actor tween target overlaps something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from AActor and if the Tween type is either "Move" or "Scale".
     * Use only in Blueprints.
     */
    UPROPERTY(BlueprintAssignable)
    FBP_OnTweenActorBeginOverlapVector OnTweenActorBeginOverlap;

    /**
     * @brief Delegate called when the PrimitiveComponent tween target is hit by something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from UPrimitiveComponent and if the Tween type is either "Move" or "Scale".
     * Use only in Blueprints.
     */
    UPROPERTY(BlueprintAssignable)
    FBP_OnTweenPrimitiveComponentHitVector OnTweenPrimitiveComponentHit;

    /**
     * @brief Delegate called when the PrimitiveComponent tween target overlaps something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from UPrimitiveComponent and if the Tween type is either "Move" or "Scale".
     * Use only in Blueprints.
     */
    UPROPERTY(BlueprintAssignable)
    FBP_OnTweenPrimitiveComponentBeginOverlapVector OnTweenPrimitiveComponentBeginOverlap;


    /*
     **************************************************************************
     * C++ delegates
     **************************************************************************
     */

    /// @brief Delegate called when the Tween starts (if it loops then it's called at each loop begin). Use only in C++. 
    FOnTweenVectorChange OnTweenStartDelegate;

    /// @brief Delegate called at each Tween's update. Use only in C++. 
    FOnTweenVectorChange OnTweenUpdateDelegate;

    /// @brief Delegate called when the Tween ends (if it loops then it's called at each loop end). Use only in C++. 
    FOnTweenVectorChange OnTweenEndDelegate;

    /**
     * @brief Delegate called when the Actor tween target is hit by something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from AActor and if the Tween type is either "Move" or "Scale".
     * Use only in C++.
     */
    FOnTweenActorHitVector OnTweenActorHitDelegate;

    /**
     * @brief Delegate called when the Actor tween target overlaps something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from AActor and if the Tween type is either "Move" or "Scale".
     * Use only in Blueprints.
     */
    FOnTweenActorBeginOverlapVector OnTweenActorBeginOverlapDelegate;

    /**
     * @brief Delegate called when the PrimitiveComponent tween target is hit by something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from UPrimitiveComponent and if the Tween type is either "Move" or "Scale".
     * Use only in Blueprints.
     */
    FOnTweenPrimitiveComponentHitVector OnTweenPrimitiveComponentHitDelegate;

    /**
     * @brief Delegate called when the PrimitiveComponent tween target overlaps something during the Tween's execution. Only valid if the TweenTarget
     * actually inherits from UPrimitiveComponent and if the Tween type is either "Move" or "Scale".
     * Use only in Blueprints.
     */
    FOnTweenPrimitiveComponentBeginOverlapVector OnTweenPrimitiveComponentBeginOverlapDelegate;


protected:
    
    // Begin of UBaseTween interface
    virtual bool Update(float pDeltaTime, float pTimeScale) override;
    virtual void Restart(bool pRestartFromEnd) override;
    virtual void Invert(bool pShouldInvertElapsedTime = true) override;
    virtual void PrepareTween() override;
    virtual void PositionAt(bool pBeginning) override;
    virtual void PreDelay() override;
    virtual void BroadcastOnTweenStart() override;
    virtual void BroadcastOnTweenUpdate() override;
    virtual void BroadcastOnTweenEnd() override;
    virtual void OnTweenPausedInternal() override;
    virtual void OnTweenResumedInternal() override;
    virtual void OnTweenDeletedInternal() override;
    // End of UBaseTween interface

    /*
     **************************************************************************
     * Helper methods for updating individual classes
     **************************************************************************
     */

    /**
     * @brief Updates the current value for an Actor Tween.
     *
     * @param pTarget The target of the Tween.
     */
    void UpdateForActor(AActor* pTarget);

    /**
     * @brief Updates the current value for a scene component Tween.
     *
     * @param pTarget The target of the Tween.
     */
    void UpdateForSceneComponent(USceneComponent* pTarget);

    /*
     **************************************************************************
     * Helper methods for binding/unbinding hit and overlap delegates
     **************************************************************************
     */

    /**
     * @brief Helper method that bind the appropriate delegates.
     */
    void BindDelegates();

    /**
     * @brief Helper method that unbind all bounded delegates.
     */
    void UnbindDelegates();

    /**
     * @brief Function called when the tween target overlap something (only used if the
     *        appropriate delegate is bound and the tween target is an actor).
     */
    UFUNCTION()
    void OnActorBeginOverlap(AActor* pThisActor, AActor* pOtherActor);

    /**
     * @brief Function called when the tween target hits something (only used if the
     *        appropriate delegate is bound and the tween target is an actor).
     */
    UFUNCTION()
    void OnActorHit(AActor* pThisActor, AActor* pOtherActor, FVector pNormalImpulse, const FHitResult& pHit);

    /**
     * @brief Function called when the tween target overlap something (only used if the
     *        appropriate delegate is bound and the tween target is a primitive component).
     */
    UFUNCTION()
    void OnPrimitiveComponentBeginOverlap(UPrimitiveComponent* pThisComponent,
                                          AActor* pOtherActor,
                                          UPrimitiveComponent* pOtherComp,
                                          int32 pOtherBodyIndex,
                                          bool bFromSweep,
                                          const FHitResult& pSweepResult);

    /**
     * @brief Function called when the tween target hits something (only used if the
     *        appropriate delegate is bound and the tween target is a primitive component).
     */
    UFUNCTION()
    void OnPrimitiveComponentHit(UPrimitiveComponent* pThisComponent,
                                 AActor* pOtherActor,
                                 UPrimitiveComponent* pOtherComp,
                                 FVector pNormalImpulse,
                                 const FHitResult& pHitResult);
    
    
    /// @brief Type of this Tween.
    ETweenVectorType mTweenType;

    /// @brief Proxy for latent Tweens. It's only valid if it's a Latent tween, otherwise it's null.
    UPROPERTY()
    UTweenVectorLatentFactory* mTweenLatentProxy;

    /// @brief Current value of the Tween.
    FVector mCurrentValue;

    /// @brief Starting value.
    FVector mFrom;

    /// @brief Ending value.
    FVector mTo;

    /// @brief Offset used to for relative Tweens (i.e. MoveBy, ScaleBy).
    FVector mBaseOffset;

    /// @brief Defines in which space the Tween makes its update (i.e. 'world' or 'relative').
    ETweenSpace mTweenSpace;

    /// @brief If true, the Tween will be deleted if the tween target hits something. Only valid of specific objects and specific tween types.
    bool bDeleteTweenOnHit;

    /// @brief If true, the Tween will be deleted if the tween target overlaps something. Only valid of specific objects and specific tween types.
    bool bDeleteTweenOnOverlap;

    /// @brief True if the Tween has bounded functions to hit/overlap events (either because the bDeleteTweenOnXYZ was selected or a method was bounded).
    bool bHasBoundedFunctions;
};
