#ifndef Asynchrony_ForwardList_h
#define Asynchrony_ForwardList_h



#ifndef NULL
	#define NULL 0
#endif



namespace Asynchrony {
	
	template<typename T> class ForwardList {
		public:
			struct Item {
				T data;
				Item *next;
			};



			class Iterator {
				public:

					static const char TYPE_NORMAL = 0;
					static const char TYPE_BEGIN = 1;
					static const char TYPE_END = 2;



					Iterator(Item *itm, char tp = TYPE_NORMAL) : item(itm), type(tp) {}



					friend const Iterator& operator++(Iterator& it) {
						switch(it.type) {
							case TYPE_NORMAL:
								it.item = it.item->next;
								if(it.item == NULL)
									it.type = TYPE_END;
								break;
							case TYPE_BEGIN:
								it.item = it.item->next;
								if(it.item == NULL)
									it.type = TYPE_END;
								else
									it.type = TYPE_NORMAL;
								break;
							case TYPE_END:
								break;
						}
						return it;
					}



					friend const T operator*(Iterator& it) {
						return it.item->data;
					}



					friend bool operator==(const Iterator& it1, const Iterator& it2) {
						return it1.type == it2.type && it1.item == it2.item;
					}



					friend bool operator==(const Iterator& it1, const char b) {
						if(b == NULL)
							return it1.type == TYPE_END;
						else
							return false;
					}



					void insertAfter(T data) {
						if(type != TYPE_END) {
							Item *nextItem = new Item;
							nextItem->data = data;
							nextItem->next = item->next;

							item->next = nextItem;
						}
					}



					void eraseAfter() {
						if(type != TYPE_END && item->next != NULL) {
							Item *afterNext = item->next->next;
							delete item->next;
							item->next = afterNext;
						}
					}



				protected:
					Item *item;
					char type;

			};



			ForwardList() {
				beforeFirst.next = NULL;
			}



			void pushFront(T data) {
				Item *nextItem = new Item;
				nextItem->data = data;
				nextItem->next = beforeFirst.next;

				beforeFirst.next = nextItem;
			}



			Iterator beforeBegin() {
				return Iterator(&beforeFirst, Iterator::TYPE_BEGIN);
			}



			Iterator begin() {
				return Iterator(beforeFirst.next, beforeFirst.next == NULL ? Iterator::TYPE_END : Iterator::TYPE_NORMAL);
			}

		protected:
			Item beforeFirst;
	};

}



#endif