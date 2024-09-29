
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_Chatbot"; 
const char* password = "123456789";  

WebServer server(80);

const char* responses[] = {
    "hello|Hello! How can I assist you today?|Hi there! What can I do for you?|Greetings! How may I help you?",
    "health|Stay hydrated, eat a balanced diet, and exercise regularly!|Remember to get enough sleep for your health.|Regular check-ups with a doctor can help maintain your health.|A balanced diet includes fruits, vegetables, and whole grains.|Consider yoga or meditation for mental wellness.",
    "study|Try studying in short bursts with breaks in between.|Creating a study schedule can improve your efficiency.|Use flashcards for better retention of information.|Study in a quiet place to minimize distractions.|Form study groups to learn from peers.",
    "joke|Why don't scientists trust atoms? Because they make up everything!|Why did the bicycle fall over? It was two-tired!|I told my computer I needed a break, and now it won’t stop sending me KitKat ads.|Why did the scarecrow win an award? Because he was outstanding in his field!|What do you call fake spaghetti? An impasta!",
    "emergency|In case of emergency, please contact local authorities!|If someone is injured, call for medical help immediately.|Know your escape routes in case of a fire!|Always have a first-aid kit available.|Stay calm and follow emergency protocols.",
    "bye|Goodbye! I'm here whenever you need to chat.|See you later!|Take care!|Until next time!|Have a great day!",
    "weather|The weather is usually unpredictable, check a reliable source for updates.|Make sure to dress appropriately for the weather.|Always have an umbrella handy in case of rain!",
    "exercise|Regular physical activity can boost your mood and energy levels.|Find a type of exercise you enjoy to stay motivated.|Walking is a great way to start getting fit.",
    "food|Eating a variety of foods can help you get the nutrients you need.|Cooking at home can be healthier and more satisfying.|Don’t forget to include protein in your meals!",
    "sleep|Aim for 7-9 hours of sleep each night for optimal health.|Create a bedtime routine to help improve sleep quality.|Avoid screens before bedtime to help you fall asleep faster.",
    "time management|Prioritize your tasks to manage your time effectively.|Use a planner to keep track of your schedule.|Break large tasks into smaller, manageable steps.",
    "motivation|Set small, achievable goals to keep yourself motivated.|Remember to reward yourself for accomplishments.|Stay positive and surround yourself with supportive people.",
    "stress|Practice deep breathing exercises to manage stress.|Take breaks and allow yourself some downtime.|Engage in hobbies to help reduce stress levels.",
    "learning|Always stay curious and open to new information.|Try to teach others what you've learned to reinforce your knowledge.|Use multiple sources to gather a well-rounded understanding.",
    "relationships|Communication is key to maintaining healthy relationships.|Be open and honest with those you care about.|Spend quality time together to strengthen bonds.",
    "finance|Create a budget to keep track of your spending.|Start saving early to prepare for future needs.|Consider investing to grow your wealth over time.",
    "travel|Plan your trips in advance to make the most of your time.|Traveling can be a great way to experience new cultures.|Always keep your belongings secure when traveling.",
    "environment|Reduce, reuse, recycle to help protect the planet.|Consider using public transport to reduce your carbon footprint.|Plant trees and support local conservation efforts.",
    "pets|Pets can bring joy and companionship into your life.|Regular veterinary check-ups are important for pet health.|Make sure to provide adequate exercise for your pets.",
    "creativity|Allow yourself to think outside the box and explore new ideas.|Creativity can be fostered through practice and exploration.|Don't be afraid to make mistakes in the creative process.",
    "mindfulness|Practice mindfulness to stay present in the moment.|Meditation can help enhance your mindfulness skills.|Take time each day to reflect and appreciate your surroundings.",
    "self-care|Self-care is important for maintaining your mental health.|Make time for activities that you enjoy.|Don't hesitate to ask for help when you need it.",
    "technology|Technology can enhance your learning experience.|Stay updated with the latest tech trends for better opportunities.|Always ensure your online security and privacy.",
    "gratitude|Practicing gratitude can improve your overall well-being.|Keep a gratitude journal to remind yourself of positive aspects of your life.|Expressing gratitude can strengthen relationships.",
    "reading|Reading can expand your knowledge and improve your focus.|Set aside time each day for reading.|Join a book club to share thoughts and discover new titles.",
    "hobbies|Engaging in hobbies can provide a great stress relief.|Try new activities to find what you enjoy.|Dedicate time each week to focus on your hobbies.",
    "community|Being involved in your community can provide support and connection.|Volunteer opportunities are a great way to give back.|Attend local events to meet new people.",
    "career|Networking can open doors for career advancement.|Always seek feedback to improve your skills.|Set clear career goals and work towards them.",
    "culture|Learning about different cultures can broaden your perspective.|Participate in cultural events to experience diversity.|Respect and appreciate cultural differences.",
    "family|Spend quality time with family to strengthen bonds.|Communication is key in any family relationship.|Support each other during tough times.",
    "happiness|Find joy in small things throughout your day.|Surround yourself with positive influences.|Practice self-compassion to boost happiness.",
    "philosophy|Philosophy encourages critical thinking and exploration of ideas.|Discuss philosophical questions with others to gain insights.|Read philosophical texts for deeper understanding.",
    "history|Learning from history can help prevent repeating mistakes.|Explore historical sites to appreciate your heritage.|Read about influential figures in history.",
    "art|Art can be a powerful form of expression.|Visit galleries to appreciate various artistic styles.|Try creating your own art as a therapeutic activity.",
    "science|Science helps us understand the world around us.|Stay curious and ask questions about how things work.|Engage in experiments to learn through experience.",
    "sports|Participating in sports can improve your physical fitness.|Team sports can foster camaraderie and teamwork.|Always follow safety guidelines when playing sports.",
    "fashion|Fashion is a way to express your personal style.|Stay updated with trends, but choose what suits you best.|Thrift shopping can be a fun way to find unique pieces.",
    "music|Listening to music can enhance your mood and productivity.|Learn to play an instrument to explore your musical side.|Share music with friends to bond over favorites.",
    "adventure|Life is an adventure; embrace new experiences.|Try something outside your comfort zone.|Document your adventures to cherish memories.",
    "innovation|Innovation drives progress and can change the world.|Encourage creativity in yourself and others.|Stay open to new ideas and possibilities.",
    "sustainability|Sustainable practices can help protect our planet.|Support businesses that prioritize sustainability.|Educate others on the importance of sustainability.",
    "communication|Effective communication is essential in all aspects of life.|Practice active listening to understand others better.|Use clear and concise language to convey your message.",
    "confidence|Building confidence takes time and practice.|Focus on your strengths and celebrate your achievements.|Challenge negative self-talk with positive affirmations.",
    "empathy|Empathy allows us to connect with others on a deeper level.|Practice putting yourself in someone else's shoes.|Acts of kindness can enhance feelings of empathy.",
    "technology trends|Stay informed about the latest technology trends.|Consider how technology impacts daily life.|Explore innovative solutions to modern challenges.",
    "gardening|Gardening can be a relaxing and rewarding hobby.|Start with easy-to-grow plants to build confidence.|Learn about native plants for your area.",
    "baking|Baking can be a fun and creative outlet.|Experiment with different recipes to find favorites.|Share your baked goods with friends and family for joy.",
    "photography|Photography can capture beautiful moments.|Learn about composition and lighting for better photos.|Explore different styles, like portrait or landscape photography.",
    "public speaking|Practice makes perfect in public speaking.|Know your audience to tailor your message.|Use visual aids to enhance your presentations.",
    "nutrition|Understanding nutrition is key to a healthy lifestyle.|Meal prep can save time and ensure balanced eating.|Consult a nutritionist for personalized advice.",
    "work-life balance|Strive for a healthy work-life balance.|Set boundaries to protect your personal time.|Prioritize self-care alongside work commitments.",
    "mental health|Prioritize your mental health by seeking support when needed.|Practice self-compassion and mindfulness.|Engage in activities that bring you joy.",
    "self-improvement|Continuous self-improvement can lead to personal growth.|Set realistic goals and track your progress.|Seek feedback to identify areas for improvement.",
    "assertiveness|Being assertive helps you communicate your needs.|Practice saying no when necessary.|Respect the opinions and boundaries of others.",
    "financial literacy|Understanding finances is crucial for independence.|Learn about budgeting, saving, and investing.|Seek resources to improve your financial knowledge.",
    "travel tips|Research destinations ahead of time for a smoother trip.|Pack light and only take essentials.|Keep important documents organized and accessible.",
    "life skills|Developing life skills can enhance independence.|Practice cooking, budgeting, and time management.|Learn problem-solving techniques for daily challenges.",
    "coaching|Coaching can help individuals reach their goals.|Find a coach that aligns with your needs and values.|Set clear objectives for coaching sessions.",
    "teamwork|Teamwork fosters collaboration and creativity.|Value diverse perspectives within a team.|Communicate openly and supportively with team members.",
    "decision-making|Effective decision-making involves evaluating options.|Consider both short-term and long-term consequences.|Trust your instincts while gathering information.",
    "volunteering|Volunteering can enrich your life and community.|Find opportunities that align with your interests.|Be open to meeting new people through volunteering.",
    "self-discipline|Self-discipline is essential for achieving goals.|Create routines to help maintain focus.|Practice delaying gratification to strengthen self-control.",
    "cooking|Cooking at home can be healthier and more economical.|Experiment with different cuisines to expand your palate.|Invite friends over for a cooking night.",
    "technology education|Technology education is vital in today's world.|Stay updated with the latest tools and resources.|Encourage children to explore technology creatively.",
    "diy|DIY projects can be fun and rewarding.|Start with simple projects to build confidence.|Share your creations with friends and family.",
    "safety|Safety is paramount in every situation.|Always follow safety guidelines at home and work.|Educate yourself on emergency procedures.",
    "networking|Networking can open doors for career opportunities.|Attend industry events to meet professionals.|Utilize social media platforms to connect with others.",
    "personal branding|Personal branding can enhance your career prospects.|Be consistent in your messaging and online presence.|Showcase your skills and experiences authentically.",
    "disaster preparedness|Prepare an emergency kit with essentials.|Stay informed about local hazards and plans.|Practice emergency drills with your family.",
    "environmental awareness|Increase your awareness of environmental issues.|Participate in local cleanup events.|Support policies that protect natural resources.",
    "digital literacy|Digital literacy is crucial in the modern world.|Learn to navigate online tools and platforms effectively.|Teach others about internet safety and privacy.",
    "career development|Invest in your career development through training.|Seek mentors to guide you in your professional journey.|Set career goals and review them regularly.",
    "creativity exercises|Engage in creativity exercises to boost innovation.|Try brainstorming sessions with others.|Allow time for free exploration of ideas.",
    "effective feedback|Providing effective feedback is crucial for growth.|Use the “sandwich method” for delivering criticism.|Encourage open dialogue and receptiveness to feedback.",
    "stress management|Implement stress management techniques into your routine.|Practice relaxation exercises regularly.|Identify triggers and develop coping strategies.",
    "sustainability practices|Adopt sustainability practices in daily life.|Reduce single-use plastics and recycle.|Support local businesses that prioritize sustainability.",
    "art therapy|Art therapy can promote emotional healing.|Engage in creative expression through various mediums.|Seek professional guidance for therapeutic benefits.",
    "cognitive development|Cognitive development is essential during childhood.|Encourage problem-solving and critical thinking.|Provide a stimulating environment for learning.",
    "cultural awareness|Cultural awareness promotes empathy and understanding.|Participate in cultural exchange programs.|Educate yourself about different traditions and values.",
    "life coaching|Life coaching can help clarify your goals.|Seek a certified coach for professional guidance.|Regularly assess your progress and adapt as needed.",
    "personal finance|Understanding personal finance is key to financial independence.|Create a budget and stick to it.|Invest in your future through savings and investment.",
    "digital citizenship|Being a good digital citizen is essential.|Practice respect and kindness online.|Educate others about online safety and privacy.",
    "personal growth|Focus on personal growth to enhance your life.|Set goals and challenge yourself.|Reflect on your experiences to learn and improve.",
    "environmental sustainability|Commit to practices that support environmental sustainability.|Educate others on the importance of conservation.|Reduce your carbon footprint where possible.",
    "emotional intelligence|Emotional intelligence enhances interpersonal skills.|Practice self-awareness and empathy.|Seek feedback on emotional responses.",
    "communication skills|Developing communication skills is vital for success.|Practice active listening and clear expression.|Engage in discussions to refine your skills.",
    "conflict resolution|Effective conflict resolution is essential in relationships.|Use mediation techniques to resolve disputes.|Practice empathy to understand different perspectives.",
    "career planning|Career planning helps you identify your path.|Research potential careers and necessary qualifications.|Network with professionals in your desired field.",
    "social skills|Social skills are important for building relationships.|Practice engaging in conversations and reading social cues.|Join clubs or groups to meet new people.",
    "mental resilience|Building mental resilience can help you face challenges.|Practice positive thinking and self-care.|Seek support when facing difficult situations.",
    "productivity tips|Use productivity techniques to maximize your time.|Set specific, measurable goals for tasks.|Take breaks to maintain focus and energy.",
    "self-reflection|Regular self-reflection promotes personal growth.|Keep a journal to track your thoughts and progress.|Ask yourself challenging questions to deepen understanding.",
    "emergency preparedness|Develop a plan for emergencies with your family.|Practice drills for different emergency scenarios.|Stay informed about local emergency services.",
    "interpersonal relationships|Building strong interpersonal relationships is essential.|Practice empathy and active listening.|Engage in regular check-ins with loved ones.",
    "self-esteem|Building self-esteem is crucial for personal development.|Practice self-affirmation and positive self-talk.|Surround yourself with supportive people.",
    "conflict management|Learn effective conflict management strategies.|Stay calm and focused during disagreements.|Seek common ground to resolve conflicts.",
    "cultural competency|Cultural competency enhances communication.|Learn about different cultural practices and values.|Engage in conversations to deepen understanding.",
    "goal setting|Set specific, achievable goals to guide your actions.|Regularly review and adjust your goals as needed.|Celebrate your achievements, no matter how small.",
    "self-awareness|Developing self-awareness is key to personal growth.|Reflect on your emotions and behaviors.|Seek feedback from others to gain perspective.",
    "team dynamics|Understanding team dynamics can improve collaboration.|Encourage open communication within teams.|Recognize and respect individual strengths.",
    "decision-making skills|Improve your decision-making skills through practice.|Evaluate pros and cons before making choices.|Learn from past decisions to inform future ones.",
    "interpersonal communication|Strong interpersonal communication is vital for success.|Practice clear expression and active listening.|Be open to feedback and differing opinions.",
    "civic engagement|Civic engagement strengthens communities.|Participate in local governance and initiatives.|Educate others on civic responsibilities.",
    "workplace skills|Develop key workplace skills to enhance employability.|Focus on communication, teamwork, and problem-solving.|Seek opportunities for professional development.",
    "personal values|Understanding your personal values can guide your actions.|Reflect on what matters most to you.|Make decisions that align with your values.",
    "technology integration|Integrating technology into education enhances learning.|Explore tools that facilitate collaboration.|Stay informed about emerging educational technologies.",
    "volunteering benefits|Volunteering provides numerous benefits for personal growth.|Gain new skills and experiences through volunteering.|Meet new people and expand your network.",
    "cognitive skills|Enhance your cognitive skills through practice.|Engage in puzzles, games, and critical thinking exercises.|Seek challenges that promote mental agility.",
    "self-motivation|Self-motivation is crucial for achieving goals.|Set personal incentives to stay motivated.|Reflect on your reasons for pursuing goals.",
    "active listening|Active listening is essential for effective communication.|Practice reflecting back what you hear to ensure understanding.|Avoid interrupting when others are speaking.",
    "career transitions|Career transitions can be challenging but rewarding.|Research new fields and necessary skills.|Seek mentorship during your transition.",
    "cultural sensitivity|Cultural sensitivity fosters respect and understanding.|Be mindful of cultural differences in communication.|Educate yourself on various cultural practices.",
    "project management|Effective project management is vital for success.|Use planning tools to keep projects on track.|Communicate clearly with team members about goals.",
    "networking skills|Develop networking skills to build professional relationships.|Practice introducing yourself and engaging in conversations.|Follow up with contacts to maintain connections.",
    "lifestyle changes|Making lifestyle changes can improve health and well-being.|Set small, achievable goals to create lasting change.|Seek support from friends and family.",
    "business skills|Develop business skills to enhance your career prospects.|Focus on financial literacy, marketing, and management.|Seek opportunities for internships and real-world experience.",
    "mindful living|Practice mindful living to enhance your well-being.|Stay present in each moment and appreciate your surroundings.|Engage in activities that promote mindfulness.",
    "professional development|Invest in your professional development for growth.|Attend workshops, webinars, and conferences.|Seek feedback to continuously improve your skills.",
    "resilience training|Resilience training can help you face challenges effectively.|Practice coping strategies and stress management techniques.|Seek support from others to build resilience.",
    "leadership skills|Develop leadership skills to enhance your influence.|Practice decision-making and problem-solving.|Encourage teamwork and collaboration.",
    "workplace wellness|Promoting workplace wellness benefits employees.|Implement programs that support physical and mental health.|Encourage a healthy work-life balance.",
    "strategic thinking|Strategic thinking enhances decision-making and planning.|Evaluate options critically and anticipate outcomes.|Seek diverse perspectives to inform your strategies.",
    "life skills education|Life skills education promotes independence and resilience.|Teach essential skills like budgeting and communication.|Engage students in practical, real-world experiences.",
    "adaptability|Adaptability is key to navigating change successfully.|Stay open to new ideas and flexible in your approach.|Seek opportunities to develop adaptability skills.",
    "social responsibility|Being socially responsible enhances community well-being.|Engage in actions that benefit society.|Encourage others to participate in community initiatives.",
    "career exploration|Career exploration helps identify interests and strengths.|Conduct informational interviews with professionals.|Attend career fairs and workshops.",
    "financial planning|Effective financial planning supports long-term stability.|Create a budget and savings plan to reach financial goals.|Seek professional advice when needed.",
    "health literacy|Health literacy empowers individuals to make informed decisions.|Stay informed about health resources and services.|Encourage healthy behaviors through education.",
    "self-care routines|Establishing self-care routines is essential for well-being.|Make time for relaxation and personal interests.|Seek balance between responsibilities and self-care.",
    "workplace diversity|Promoting workplace diversity enhances creativity.|Encourage an inclusive environment that values differences.|Implement training programs to raise awareness.",
    "online safety|Practicing online safety is crucial in today’s digital age.|Use strong passwords and enable two-factor authentication.|Educate others about phishing scams and online risks.",
    "strategic planning|Strategic planning is vital for achieving organizational goals.|Set clear objectives and evaluate progress regularly.|Involve team members in the planning process.",
    "mental agility|Mental agility enhances problem-solving and decision-making.|Engage in activities that challenge your thinking.|Practice mindfulness to improve focus.",
    "personal mission|Establishing a personal mission can guide your actions.|Reflect on your values and goals to create a mission statement.|Use your mission to inform decision-making.",
    "civic education|Civic education promotes informed citizenship.|Teach the importance of civic responsibilities.|Encourage participation in community decision-making.",
    "job search skills|Develop job search skills to enhance employability.|Create a standout resume and practice interview techniques.|Network to discover job opportunities.",
    "relationship building|Building strong relationships is essential for success.|Practice empathy and open communication.|Engage in regular check-ins with colleagues.",
    "emotional wellness|Emotional wellness is key to overall health.|Practice self-compassion and mindfulness.|Seek support when facing emotional challenges.",
    "community service|Community service benefits individuals and society.|Engage in local projects to make a difference.|Encourage others to participate in service activities.",
    "entrepreneurial skills|Develop entrepreneurial skills to enhance innovation.|Foster creativity and problem-solving abilities.|Seek mentorship to guide your entrepreneurial journey."
};


void setup() {
    Serial.begin(115200);
    
    
    WiFi.softAP(ssid, password);
    
    Serial.println("Access Point started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    
    server.on("/", HTTP_GET, handleRoot);
    server.on("/chat", HTTP_GET, handleChat);
    
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}

void handleRoot() {
    String html = "<html><body>";
    html += "<h1>Simple Chatbot</h1>";
    html += "<form action=\"/chat\" method=\"GET\">";
    html += "Enter your message: <input type=\"text\" name=\"msg\">";
    html += "<input type=\"submit\" value=\"Send\">";
    html += "</form>";
    html += "<h2>Expected Storage Usage</h2>";
    html += "<p>This chatbot uses approximately 50-80 KB of flash memory.</p>";
    html += "<p>Feel free to interact with me!</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleChat() {
    String message = server.arg("msg");
    message.toLowerCase(); // Convert to lowercase for case-insensitive comparison
    String response = getResponse(message);
    
    String html = "<html><body>";
    html += "<h1>Chatbot Response</h1>";
    html += "<p>You: " + message + "</p>";
    html += "<p>Bot: " + response + "</p>";
    html += "<a href=\"/\">Back</a>";
    html += "</body></html>";
    server.send(200, "text/html", html);
}

String getResponse(String message) {
    for (const char* responseEntry : responses) {
        String entry = responseEntry;
        String category = entry.substring(0, entry.indexOf('|'));
        
        if (message.indexOf(category) >= 0) {
            // Get responses
            entry.remove(0, category.length() + 1);
            int start = 0;
            int end = entry.indexOf('|');
            String response = "";
            while (end != -1) {
                response += entry.substring(start, end) + "<br/>";
                start = end + 1;
                end = entry.indexOf('|', start);
            }
            response += entry.substring(start); // Last response
            return response;
        }
    }
    return "I don't understand that. Try asking something else!";
}
