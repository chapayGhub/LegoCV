//
//  OCVMat.h
//  LegoCV
//
//  Created by Dal Rupnik on 16/01/2017.
//  Copyright © 2017 Unified Sense. All rights reserved.
//

#import "OCVMatDataAllocator.h"

#import "OCVTypes.h"
#import "OCVSize.h"
#import "OCVMatExpr.h"
#import "OCVInputArrayable.h"
#import "OCVOutputArrayable.h"
#import "OCVInputOutputArrayable.h"

/*!
 *  OCVMat is a simple Objective-C wrapper around cv::Mat instance.
 */
@interface OCVMat : OCVMatDataAllocator <OCVInputArrayable, OCVOutputArrayable, OCVInputOutputArrayable>

#pragma mark - Public Properties

@property (nonatomic, readonly) NSInteger rows;
@property (nonatomic, readonly) NSInteger cols;

@property (nonatomic, readonly) NSInteger dims;

@property (nonatomic, readonly) BOOL isSubmatrix;
@property (nonatomic, readonly) BOOL isContinuous;

@property (nonatomic, readonly) BOOL isEmpty;
@property (nonatomic, readonly) NSInteger total;

@property (nonatomic, readonly) NSInteger elemSize;
@property (nonatomic, readonly) NSInteger elemSize1;

@property (nonatomic, readonly) OCVDepthType type;

@property (nonatomic, readonly) NSInteger channels;

@property (nonatomic, readonly) OCVSize size;

#pragma mark - Initialization

- (instancetype)initWithRows:(NSInteger)rows cols:(NSInteger)cols;
- (instancetype)initWithRows:(NSInteger)rows cols:(NSInteger)cols type:(OCVDepthType)type channels:(NSInteger)channels;
- (instancetype)initWithSize:(OCVSize)size type:(OCVDepthType)type channels:(NSInteger)channels;
- (instancetype)initWithMat:(OCVMat *)mat;

#pragma mark - Public Methods

// TODO: Should replace with NSCopying
- (OCVMat *)clone;

#pragma mark - Operations

- (OCVMat *)reshapeWithChannels:(NSInteger)channels;
- (OCVMat *)reshapeWithChannels:(NSInteger)channels rows:(NSInteger)rows;

- (OCVMat *)transpose;

- (OCVMat *)inverse;
- (OCVMat *)inverseWithMethod:(NSInteger)method;

- (OCVMat *)multiplyWithArray:(id<OCVInputArrayable>)inputArray;
- (OCVMat *)multiplyWithArray:(id<OCVInputArrayable>)inputArray scale:(double)scale;

- (OCVMat *)crossWithArray:(id<OCVInputArrayable>)inputArray;

- (double)dotWithArray:(id<OCVInputArrayable>)inputArray;

#pragma mark - Public Factory Methods

+ (instancetype)zerosWithRows:(NSInteger)rows cols:(NSInteger)cols type:(NSInteger)type;
+ (instancetype)zerosWithSize:(OCVSize *)size type:(NSInteger)type;

+ (instancetype)onesWithRows:(NSInteger)rows cols:(NSInteger)cols type:(NSInteger)type;
+ (instancetype)onesWithSize:(OCVSize *)size type:(NSInteger)type;

@end

#pragma mark - iOS Extensions

#import <UIKit/UIKit.h>

@interface OCVMat (UIKit)

- (instancetype)initWithImage:(UIImage *)image;
- (UIImage *)image;

@end

#import <CoreGraphics/CoreGraphics.h>

@interface OCVMat (CoreGraphics)
- (instancetype)initWithImageRef:(CGImageRef)imageRef;
- (instancetype)initWithCGSize:(CGSize)size;
- (instancetype)initWithCGSize:(CGSize)size type:(OCVDepthType)type channels:(NSInteger)channels;

/*!
 *  Construct image reference and returns it
 */
- (CGImageRef)imageRef;

@end

#import <CoreVideo/CoreVideo.h>

@interface OCVMat (CoreVideo)

- (instancetype)initWithPixelBuffer:(CVPixelBufferRef)buffer;

@end
