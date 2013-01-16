#ifndef __MAILCORE_MCIMAPSEARCHEXPRESSION_H_

#define __MAILCORE_MCIMAPSEARCHEXPRESSION_H_

#include <mailcore/MCBaseTypes.h>
#include <mailcore/MCMessageConstants.h>

namespace mailcore {

	class IMAPSearchExpression : public Object {
	private:
		IMAPSearchKind mKind;
		String * mHeader;
		String * mValue;
		IMAPSearchExpression * mLeftExpression;
		IMAPSearchExpression * mRightExpression;
		void init();
		
	public:
		IMAPSearchExpression();
		IMAPSearchExpression(IMAPSearchExpression * other);
		virtual ~IMAPSearchExpression();
		
		virtual String * description();
		virtual Object * copy();
		
		virtual IMAPSearchKind kind();
		virtual String * header();
		virtual String * value();
		virtual IMAPSearchExpression * leftExpression();
		virtual IMAPSearchExpression * rightExpression();
		
		static IMAPSearchExpression * searchFrom(String * value);
		static IMAPSearchExpression * searchRecipient(String * value);
		static IMAPSearchExpression * searchSubject(String * value);
		static IMAPSearchExpression * searchContent(String * value);
		static IMAPSearchExpression * searchHeader(String * header, String * value);
		static IMAPSearchExpression * searchAnd(IMAPSearchExpression * left, IMAPSearchExpression * right);
		static IMAPSearchExpression * searchOr(IMAPSearchExpression * left, IMAPSearchExpression * right);
	};
	
}

#endif
