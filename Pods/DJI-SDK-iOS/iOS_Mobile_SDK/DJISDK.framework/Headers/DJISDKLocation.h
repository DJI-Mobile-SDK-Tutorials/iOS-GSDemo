//
//  DJISDKLocation.h
//  DJISDK
//
//  Copyright © 2017, DJI. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>

@interface DJISDKLocation : CLLocation

+(instancetype) locationWithLatitude:(double)latitude longitude:(double)longitude altitude:(double)altitude;
+(instancetype) locationWithCoordinate:(CLLocationCoordinate2D)coordinate;

@end
