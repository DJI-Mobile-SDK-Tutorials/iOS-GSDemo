//
//  DJIBaseComponent.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <DJISDK/DJISDKFoundation.h>
#import <DJISDK/DJIBaseProduct.h>

NS_ASSUME_NONNULL_BEGIN
@class DJIBaseComponent;
@class DJIBaseProduct;


/**
 *  Abstract class for components in a DJI Product. A component can be a camera,
 *  gimbal, remote controller, etc.  A DJI product consists of several components.
 *  All components of a product are subclasses of `DJIBaseComponent` and can be
 *  accessed directly from the product objects (`DJIAircraft` or `DJIHandheld`).
 */
@interface DJIBaseComponent : NSObject


/**
 *  `YES` if the component is connected.
 */
@property (assign, nonatomic, readonly, getter = isConnected) BOOL connected;


/**
 *  Returns the firmware version of the component. Each component will  have a
 *  different firmware version, the combination of which will  form the package
 *  firmware version `getFirmwarePackageVersionWithCompletion` found in
 *  `DJIBaseProduct`.
 *  
 *  @param version The component's firmware version.
 *  @param error Error retrieving the value.
 *  @param block Completion block
 */
- (void)getFirmwareVersionWithCompletion:(void (^)(NSString *_Nullable version, NSError *_Nullable error))block;


/**
 *  Gets the serial number of the component. Depending on the component, this serial
 *  number might not match the serial number found  on the physical component.
 *  
 *  @param serialNumber The serial number of the component.
 *  @param error Error retrieving the value.
 *  @param block Completion block that receives the getter result.
 */
- (void)getSerialNumberWithCompletion:(void (^)(NSString *_Nullable serialNumber, NSError *_Nullable error))block;

@end

NS_ASSUME_NONNULL_END
