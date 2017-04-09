//
//  DJIAircraft.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseProduct.h>

@class DJIFlightController;
@class DJIRemoteController;
@class DJIMobileRemoteController;

NS_ASSUME_NONNULL_BEGIN


/**
 *  The Aircraft's model name is unknown.
 */
extern NSString *const DJIAircraftModelNameUnknownAircraft;


/**
 *  The aircraft's model name is Inspire 1.
 */
extern NSString *const DJIAircraftModelNameInspire1;


/**
 *  The aircraft's model name is Inspire 1 Pro.
 */
extern NSString *const DJIAircraftModelNameInspire1Pro;


/**
 *  The aircraft's model name is Inspire 1 Raw.
 */
extern NSString *const DJIAircraftModelNameInspire1RAW;


/**
 *  The aircraft's model name is Phantom 3 Professional.
 */
extern NSString *const DJIAircraftModelNamePhantom3Professional;


/**
 *  The aircraft's model name is Phantom 3 Advanced.
 */
extern NSString *const DJIAircraftModelNamePhantom3Advanced;


/**
 *  The aircraft's model name is Phantom 3 Standard.
 */
extern NSString *const DJIAircraftModelNamePhantom3Standard;


/**
 *  The aircraft's model name is Phantom 3 4K.
 */
extern NSString *const DJIAircraftModelNamePhantom34K;


/**
 *  The aircraft's model name is Matrice 100.
 */
extern NSString *const DJIAircraftModelNameMatrice100;


/**
 *  The aircraft's model name is Phantom 4.
 */
extern NSString *const DJIAircraftModelNamePhantom4;


/**
 *  The aircraft's model name is Matrice 600.
 */
extern NSString *const DJIAircraftModelNameMatrice600;


/**
 *  The aircraft's model name is Matrice 600 Pro.
 */
extern NSString *const DJIAircraftModelNameMatrice600Pro;


/**
 *  The aircraft flight controller's model name is A3.
 */
extern NSString *const DJIAircraftModelNameA3;


/**
 *  The aircraft flight controller's model name is N3.
 */
extern NSString *const DJIAircraftModelNameN3;


/**
 *  The aircraft's model name is Mavic Pro.
 */
extern NSString *const DJIAircraftModelNameMavicPro;


/**
 *  The aircraft's model name is Phantom 4 Pro.
 */
extern NSString *const DJIAircraftModelNamePhantom4Pro;


/**
 *  The aircraft's model name is Inspire 2.
 */
extern NSString *const DJIAircraftModelNameInspire2;



/**
 *  Aircraft product class, which includes basic product information and access to
 *  all components (such as flight controller, battery etc.). This object is
 *  accessed  from `product` in `DJISDKManager`. Aircraft components are defined in
 *  both `DJIAircraft` and its parent `DJIBaseProduct`.
 */
@interface DJIAircraft : DJIBaseProduct



/**
 *  Returns an instance of the aircraft's flight controller.
 */
@property(nonatomic, readonly) DJIFlightController *_Nullable flightController;


/**
 *  Returns an array of the aircraft's batteries. It is used when the aircraft has
 *  multiple batteries, e.g. Matrice 600.
 */
@property(nonatomic, readonly) NSArray<DJIBattery *> *_Nullable batteries;


/**
 *  Returns an instance of the aircraft's remote controller.
 */
@property(nonatomic, readonly) DJIRemoteController *_Nullable remoteController;


/**
 *  A simulated remote controller on the mobile device. It is supported only by
 *  Mavic Pro using WiFi.
 */
@property(nonatomic, readonly) DJIMobileRemoteController *_Nullable mobileRemoteController;

@end
NS_ASSUME_NONNULL_END
