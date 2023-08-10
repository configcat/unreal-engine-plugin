﻿// Copyright (c) ConfigCat 2023. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "ConfigCatSettings.generated.h"

USTRUCT()
struct FProxyAuthentication
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Proxy)
	FString User;

	UPROPERTY(EditAnywhere, Category = Proxy)
	FString Password;
};

UENUM()
enum class EDataGovernance : uint8
{
	EuOnly,
	Global,
};

UENUM()
enum class EPollingMode : uint8
{
	Auto,
	LazyLoad,
	ManualPoll,
};

/**
 * Holds configuration for integrating the ConfigCat feature flags SDK
 */
UCLASS(Config = ConfigCat)
class CONFIGCAT_API UConfigCatSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Integration")
	FString SdkKey = TEXT("kW7bCP7Yj0iJ9f1EAmRBhw/g9rekvUdhEOQ2Ryo0fFqtQ");
	/**
	 * @brief The base ConfigCat CDN url.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	FString BaseUrl = TEXT("");
	/**
	 * @brief Set this parameter to be in sync with the Data Governance preference on the [Dashboard](https://app.configcat.com/organization/data-governance).
	 * @note Only Organization Admins have access
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	EDataGovernance DataGovernance = EDataGovernance::Global;
	/**
	 * @brief The number of milliseconds to wait for the server to make the initial connection
	 * @note 0 means it never times out during transfer
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "ms"))
	uint32 ConnectionTimeout = 8000;
	/**
	 * @brief The number of milliseconds to wait for the server to respond before giving up
	 * @note 0 means it never times out during transfer
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (ClampMin = "0", UIMin = "0", ForceUnits = "ms"))
	uint32 ReadTimeout = 5000;
	/**
	 * @brief The polling mode.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	EPollingMode PollingMode;
	/**
	 * @brief Sets at least how often this policy should fetch the latest configuration and refresh the cache.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (EditCondition = "PollingMode == EPollingMode::Custom", EditConditionHides, ClampMin = "0", UIMin = "0", ForceUnits = "s"))
	uint32 AutoPollInterval = 60;
	/**
	 * @brief Sets the maximum waiting time between initialization and the first config acquisition in seconds.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (EditCondition = "PollingMode == EPollingMode::Custom", EditConditionHides, ClampMin = "0", UIMin = "0", ForceUnits = "s"))
	uint32 MaxInitWaitTime = 5;
	/**
	 * @brief Sets how long the cache will store its value before fetching the latest from the network again.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client", meta = (EditCondition = "PollingMode == EPollingMode::LazyLoad", EditConditionHides, ClampMin = "0", UIMin = "0", ForceUnits = "s"))
	uint32 CacheRefreshInterval;
	/**
	 * @brief Proxy addresses. e.g. { "https": "your_proxy_ip:your_proxy_port" }
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Proxy")
	TMap<FString, FString> Proxies;
	/**
	 * @brief Proxy authentication.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Proxy")
	TMap<FString, FProxyAuthentication> ProxyAuthentications;
	/**
	 * @brief Indicates whether the SDK should be initialized in offline mode or not.
	 */
	UPROPERTY(Config, EditAnywhere, Category = "ConfigCat|Client")
	bool bStartOffline;

private:
	// Begin UDeveloperSettings interface
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	virtual FName GetSectionName() const override;
#if WITH_EDITOR
	virtual FText GetSectionText() const override;
#endif
	// End UDeveloperSettings interface
};
