//
//  RFQuiltLayout.h
//
//  Created by Bryce Redd on 12/7/12.
//  Copyright (c) 2012. All rights reserved.
//

#import <UIKit/UIKit.h>


@protocol RFQuiltLayoutDelegate <UICollectionViewDelegate>
@optional

- (CGSize)blockSizeForItemAtIndexPath:(NSIndexPath *)indexPath; // defaults to 1x1
- (UIEdgeInsets)insetForItemAtIndexPath:(NSIndexPath *)indexPath; // defaults to uiedgeinsetszero

/*
 Limitation: insets in the axis opposite to the scrolling axis must be constant across all sections.
 Use the sectionInset property instead.
 */
- (UIEdgeInsets)insetForSectionAtIndex:(NSInteger)section; // defaults to uiedgeinsetszero
@end


@interface RFQuiltLayout : UICollectionViewLayout
@property (nonatomic, weak) IBOutlet NSObject<RFQuiltLayoutDelegate>* delegate;

@property (nonatomic) CGSize itemBlockSize; // defaults to 100x100
@property (nonatomic) UIEdgeInsets itemInset; // effective only if delegate is not implemented
@property (nonatomic) UIEdgeInsets sectionInset; // effective only if delegate is not implemented
@property (nonatomic) UICollectionViewScrollDirection scrollDirection; // defaults to vertical
@property (nonatomic) CGSize headerReferenceSize; // defaults to CGSizeZero
@property (nonatomic) CGSize footerReferenceSize; // defaults to CGSizeZero

// only use this if you don't have more than 1000ish items.
// this will give you the correct size from the start and
// improve scrolling speed, at the cost of time at the beginning
@property (nonatomic) BOOL prelayoutEverything;

@property(nonatomic) CGPoint firstOpenSpace;
@property(nonatomic) CGPoint furthestBlockPoint;

// this will be a 2x2 dictionary storing nsindexpaths
// which indicate the available/filled spaces in our quilt
@property(nonatomic) NSMutableDictionary* indexPathByPosition;

// indexed by "section, row" this will serve as the rapid
// lookup of block position by indexpath.
@property(nonatomic) NSMutableDictionary* positionByIndexPath;

@property(nonatomic, assign) BOOL hasPositionsCached;

// previous layout cache.  this is to prevent choppiness
// when we scroll to the bottom of the screen - uicollectionview
// will repeatedly call layoutattributesforelementinrect on
// each scroll event.  pow!
@property(nonatomic) NSArray* previousLayoutAttributes;
@property(nonatomic) CGRect previousLayoutRect;

// remember the last indexpath placed, as to not
// relayout the same indexpaths while scrolling
@property(nonatomic) NSIndexPath* lastIndexPathPlaced;

- (NSArray *)indexPathsInRect:(CGRect)rect;
- (CGRect) frameForIndexPath:(NSIndexPath*)indexPath;
- (UIEdgeInsets)sectionInsetForSection:(NSInteger)section;

@end
