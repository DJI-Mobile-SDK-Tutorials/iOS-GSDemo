//
//  DJIAirLink.h
//  DJISDK
//
//  Copyright © 2015, DJI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <DJISDK/DJIBaseComponent.h>

@class DJIAirLink;

@class DJIWiFiLink;
@class DJILightbridgeLink;
@class DJIOcuSyncLink;

NS_ASSUME_NONNULL_BEGIN


/**
 *  This protocol provides delegate methods that notify user of signal  quality
 *  update for wireless downlink and uplink.
 */
@protocol DJIAirLinkDelegate <NSObject>

@optional


/**
 *  Updated signal quality in percent for the wireless downlink (from aircraft to
 *  remote  controller). This link transfers all information from aircraft to remote
 *  controller,  which is predominantly video information. Signal quality is a
 *  function of signal  strength, interference and data rate. Signal quality will be
 *  more susceptible to weak  signal strengths or high interference when the data
 *  rate is high.
 *  
 *  @param airLink The air link from aircraft to remote controller.
 *  @param quality The signal quality in percent with range [0, 100], where 100 is the best quality.
 */
-(void)airLink:(DJIAirLink * _Nonnull)airLink didUpdateDownlinkSignalQuality:(NSUInteger)quality;


/**
 *  Updated signal quality in percent for the wireless uplink (from remote
 *  controller to  aircraft). This link transfers all information from the remote
 *  controller to to the  aircraft, which is predominantly control information.
 *  
 *  @param airLink The air link from remote controller to aircraft.
 *  @param quality The signal quality in percent with range [0, 100], where 100 is the best quality.
 */
-(void)airLink:(DJIAirLink * _Nonnull)airLink didUpdateUplinkSignalQuality:(NSUInteger)quality;

@end


/**
 *  This class contains information about the wireless link between the aircraft and
 *  the remote controller, the aircraft and the mobile device or the handheld
 *  product and the mobile device. To determine whether a particular wireless link
 *  is supported, check the isSupported flag. This object is available from the
 *  `DJIAircraft` or `DJIHandheld` object which is a subclass of `DJIBaseProduct`.
 */
@interface DJIAirLink : DJIBaseComponent


/**
 *  Return the delegate of DJIAirLink.
 */
@property(nonatomic, weak, nullable) id<DJIAirLinkDelegate> delegate;


/**
 *  `YES` if WiFi Air Link is supported.
 *  
 *  @return A boolean value.
 */
@property (nonatomic, readonly) BOOL isWiFiLinkSupported;


/**
 *  `YES` if Lightbridge Air Link is supported.
 *  
 *  @return A boolean value.
 */
@property (nonatomic, readonly) BOOL isLightbridgeLinkSupported;


/**
 *  `YES` if the OcuSync Link is supported. OcuSync Link is only supported by Mavic
 *  Pro.
 *  
 *  @return A boolean value.
 */
@property (nonatomic, readonly) BOOL isOcuSyncLinkSupported;


/**
 *  Returns the WiFi Air Link if it is available.
 */
@property (nonatomic, readonly, nullable) DJIWiFiLink *wifiLink;


/**
 *  Returns the Lightbridge Air Link if it is available.
 */
@property (nonatomic, readonly, nullable) DJILightbridgeLink *lightbridgeLink;


/**
 *  Returns the OcuSync Link if it is available.
 */
@property (nonatomic, readonly, nullable) DJIOcuSyncLink *ocuSyncLink;

@end

NS_ASSUME_NONNULL_END

