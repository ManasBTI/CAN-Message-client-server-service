#include <iostream>
#include <memory>
#include <utility> // For std::move

class MyClass {
public:
    void doWork() const {
        std::cout << "MyClass working" << std::endl;
    }
};

int main() {
    // Acquire the resource and create a unique owner
    std::unique_ptr<MyClass> uniqueOwner = std::make_unique<MyClass>();
    uniqueOwner->doWork();

    // Cannot be copied (compiler error)
    // std::unique_ptr<MyClass> otherOwner = uniqueOwner; 

    // Ownership can be transferred using std::move
    std::unique_ptr<MyClass> newOwner = std::move(uniqueOwner);
    newOwner->doWork(); 
    
    // After the move, 'uniqueOwner' is now null and no longer owns the resource.
    if (!uniqueOwner) {
        std::cout << "uniqueOwner is empty after move" << std::endl;
    }
    
    // When 'newOwner' goes out of scope at the end of main(), 
    // the MyClass object is automatically destroyed.

    return 0;
}


tep-by-Step Implementation Plan

(CAN Message Client–Server Service — C++17)

Step 1️⃣ Define the CAN Message Model

Goal: Create a safe, self-contained representation of a CAN message.

Decisions to make

CAN ID type → uint32_t

DLC type → uint8_t

Payload → std::array<uint8_t, 8>

Message is read-only after creation

What you implement

A struct CanMessage

Constructor that:

Accepts ID, DLC, payload

Validates DLC ≤ 8

Getter functions only (const)

Why this matters

Central data model

Enforces safety

Prevents client-side mutation

Step 2️⃣ Decide Ownership & Transfer Strategy

Goal: Make ownership rules crystal clear.

Design rule

Server creates messages

Client only observes

Ownership is transferred using std::unique_ptr

What you decide

Server returns:

std::optional<std::unique_ptr<CanMessage>>


Client receives ownership but accesses data as const

Why this matters

Demonstrates modern C++ memory safety

No raw pointers

Explicit ownership transfer

Step 3️⃣ Implement the Server

Goal: Store and serve CAN messages.

Responsibilities

Know which CAN IDs are supported

Create messages on demand

Reject unsupported IDs safely

What you implement

class CanServer

Internal storage:

std::unordered_map<uint32_t, CanMessageData>

Public function:

std::optional<std::unique_ptr<CanMessage>>
requestMessage(uint32_t canId);

Behavior
Condition	Result
CAN ID supported	Create message → return it
CAN ID unsupported	Return std::nullopt
Why this matters

Clean separation of responsibilities

Server owns knowledge & creation logic

Step 4️⃣ Implement Optional Handling

Goal: Handle absence of messages safely.

What you do

Use std::optional

No nullptr

No exceptions

No error codes

Server logic
if (not found)
    return std::nullopt;

Client logic
if (response.has_value())
    use message
else
    handle unsupported ID

Why this matters

Clear intent

Explicit error handling

Modern C++ best practice

Step 5️⃣ Implement the Client

Goal: Request messages without modifying them.

Responsibilities

Send CAN ID requests

Receive optional response

Read message fields safely

What you implement

class CanClient

Function like:

void requestAndPrint(uint32_t canId);

Key rules

Client:

Does not modify message

Treats message as const

Handles std::nullopt

Why this matters

Enforces read-only access

Shows correct API usage

Step 6️⃣ Enforce Read-Only Access

Goal: Make modification impossible.

Techniques

Getter functions return const

Access message through:

const CanMessage& msg = *ptr;

What NOT to do ❌

No public mutable fields

No non-const references

Why this matters

Prevents accidental data corruption

Strong API contract

Step 7️⃣ Simulate Client–Server Communication

Goal: Tie everything together.

What you do

Instantiate server

Instantiate client

Client calls server function directly

No sockets, no threads, no CAN hardware

Example flow
Client → request CAN ID
Server → check support
Server → return optional message
Client → print or reject

Step 8️⃣ Demonstrate Ownership Transfer

Goal: Make ownership movement obvious.

How you show it

Server uses std::make_unique

Returns via std::move

Client receives owning pointer

Message auto-destroyed when pointer goes out of scope

Interview gold line 🧠

“The server creates and transfers exclusive ownership of the CAN message using std::unique_ptr, ensuring deterministic lifetime management.”

Step 9️⃣ Test Both Paths

Goal: Prove correctness.

Test cases

Supported CAN ID → message printed

Unsupported CAN ID → safe handling

DLC less than 8 → payload access limited

Client cannot modify message

Step 🔟 Final Polish

Checklist

✅ No raw pointers

✅ std::optional used correctly

✅ unique_ptr ownership clear

✅ Client–server separation

✅ Compiles with -std=c++17

🧠 Mental Model Summary

Think of it like this:

Server owns the truth → creates messages → transfers ownership → client only observes